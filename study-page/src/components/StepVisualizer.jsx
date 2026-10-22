import React, { useState } from 'react';
import CodeBlock from './CodeBlock';
import { Table, Text } from './Reading';
import { explain, stateRows } from '../visualizations/explain';
import sliding from '../data/traces/sliding-window.json';
import deque from '../data/traces/monotonic-deque.json';
import binary from '../data/traces/binary-search.json';

const records = { 'sliding-window': sliding, 'monotonic-deque': deque, 'binary-search': binary };
export const visualTopics = Object.keys(records);

function formatValue(value) {
    if (Array.isArray(value)) return `[${value.map(formatValue).join(', ')}]`;
    return typeof value === 'string' ? JSON.stringify(value) : String(value);
}

function formatExampleLabel(label) {
    return label.replace(/,\s*/g, ', ').replace(/\s*=\s*/g, ' = ');
}

export default function StepVisualizer({ topicId, code }) {
    const [caseIndex, setCaseIndex] = useState(0);
    const [index, setIndex] = useState(0);
    const data = records[topicId];
    const example = data.cases[caseIndex];
    const step = example.steps[index];
    const state = step.after;
    const values = example.input.nums || Array.from(example.input.s);
    const isBinary = topicId === 'binary-search';
    const isDeque = topicId === 'monotonic-deque';
    const [title, reason] = explain(topicId, step, example.input);
    const beforeRows = step.before ? stateRows(topicId, step.before, example.input) : [];
    const rows = stateRows(topicId, state, example.input).map(([name, value], i) => [name, beforeRows[i]?.[1] ?? '미설정', value]);
    const lines = code.trimEnd().split('\n');
    const start = Math.max(1, step.line - 2);
    const end = Math.min(lines.length, step.line + 2);
    const snippet = lines.slice(start - 1, end).join('\n');
    const markers = i => {
        const labels = [];
        if (isBinary) {
            if (state.left === i) labels.push('left');
            if (state.right === i) labels.push('right');
            if (state.mid === i) labels.push('mid');
        } else {
            if (state.left === i) labels.push(isDeque ? '구간 시작' : 'left');
            if (state.right === i && i < values.length) labels.push(isDeque ? 'i' : 'right');
        }
        return labels.join(' · ');
    };
    const active = i => isBinary ? i >= state.left && i < state.right : i >= Math.max(0, state.left) && i <= state.right;
    return <div className="step-visualizer" data-topic={topicId} data-event={step.event} data-step={index}>
        <label className="example-select">따라갈 입력<select aria-label="시각화 입력" value={caseIndex} onChange={e => { setCaseIndex(Number(e.target.value)); setIndex(0); }}>{data.cases.map((item, i) => <option key={item.id} value={i}>{formatExampleLabel(item.label)}</option>)}</select></label>
        <p className="example-input"><strong>입력</strong> {Object.entries(example.input).map(([name, value]) => `${name} = ${formatValue(value)}`).join(', ')}<br/><strong>최종 반환 / 결과</strong> {formatValue(example.expected)}</p>
        <div className="step-controls"><button onClick={() => setIndex(Math.max(0, index - 1))} disabled={index === 0}>← 이전</button><button onClick={() => setIndex(Math.min(example.steps.length - 1, index + 1))} disabled={index === example.steps.length - 1}>다음 →</button><button onClick={() => setIndex(0)} disabled={index === 0}>초기화</button><span aria-live="polite">{index + 1} / {example.steps.length} 단계</span></div>
        <div className="visual-state" role="group" aria-label="배열과 포인터">
            <p>{isBinary ? '후보 구간 [left, right) · right는 제외 끝.' : isDeque ? '현재 윈도우 [i - K + 1, i] · 시작점이 음수이면 아직 K개 미만.' : '현재 구간 [left, right] · 양 끝 포함.'}</p>
            <div className="array-strip">{values.map((value, i) => <div className={`array-entry ${active(i) ? 'in-window' : ''} ${(isBinary ? state.mid === i : state.right === i) ? 'current-element' : ''}`} key={i}><span className="index-label">{i}</span><strong className="array-cell">{value}</strong><span className="pointer-label">{markers(i)}</span></div>)}{isBinary && <div className="array-entry end-entry"><span className="index-label">N = {values.length}</span><span className="array-cell">끝</span><span className="pointer-label">{markers(values.length)}</span></div>}</div>
            {!values.length && !isBinary && <p>원소가 없는 빈 입력.</p>}
            {isDeque && <><h4>덱 · 앞 → 뒤 (인덱스 : 값)</h4><div className="deque-strip" aria-label="덱 내용">{state.dq.length ? state.dq.map(i => <span key={i}>{i} : {values[i]}</span>) : '비어 있음'}</div></>}
        </div>
        <div aria-live="polite" aria-atomic="true" className="step-reason"><h3>{step.line}행 · {title}</h3><Text>{reason}</Text></div>
        <div className="execution-grid"><CodeBlock code={snippet} name="현재 실행 부분" startLine={start} activeLine={step.line} numbered/>
        <Table headers={['변수 / 자료구조', '실행 전', '실행 후']} rows={rows} caption="현재 코드 줄의 실행 전후 상태"/></div>
        <p>위 코드는 <a href="#template">전체 템플릿</a>의 {start}–{end}행. 조건 검사도 한 단계로 표시. 다음 버튼으로 기록된 C++ 실행을 한 단계씩 이동.</p>
    </div>;
}
