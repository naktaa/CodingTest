import React from 'react';
import { Inline, Text, Table } from './Reading';
import CodeBlock from './CodeBlock';
import StepVisualizer, { visualTopics } from './StepVisualizer';
import StaticDiagram from './StaticDiagram';

export const sections = [['conditions', '어떤 문제에 쓰나요'], ['concept', '핵심 아이디어'], ['template', '전체 C++ 템플릿'], ['variables', '변수와 배열의 의미'], ['steps', '코드를 순서대로 읽기'], ['trace', '작은 입력 끝까지 따라가기'], ['mistakes', '경계·반례·복잡도'], ['solutions', '연결된 내 풀이']];

export default function TopicArticle({ topic, code, solutions, children }) {
    const lesson = topic.lesson;
    const lines = code.trimEnd().split('\n');
    function heading(i) { const [id, title] = sections[i]; return <h2><span className="section-index">{String(i + 1).padStart(2, '0')}</span>{title}<a className="heading-link" href={`#${id}`} aria-label={`${title} 바로가기`}>#</a></h2>; }
    return <article className="topic-article">
        <section id="conditions">{heading(0)}<Text>{lesson.problem}</Text><ul className="body-list">{topic.conditions.map(s => <li key={s}><Inline>{s}</Inline></li>)}</ul><h3>입력 범위와 자료형</h3><Text>{lesson.range}</Text><h3 id="optimize">완전탐색에서 줄이는 일</h3><Text>{topic.optimize}</Text></section>
        <section id="concept">{heading(1)}<Text>{lesson.idea}</Text></section>
        <section id="template">{heading(2)}<p>아래는 핵심 함수와 전역 상태를 모두 담은 C++17 기본 템플릿입니다. 입력을 전역 변수에 채운 뒤 아래에서 설명하는 진입 함수를 호출합니다.</p><CodeBlock code={code} numbered/><Text>{lesson.entry}</Text></section>
        <section id="variables">{heading(3)}<Table headers={['변수 / 배열', '정확한 의미']} rows={lesson.variables || topic.variables} caption={`${topic.title} 변수 정의`}/></section>
        <section id="steps">{heading(4)}{lesson.walkthrough.map((part, i) => <div className="walkthrough" key={i}><h3>{i + 1}. {part.title}</h3><CodeBlock code={lines.slice(part.from - 1, part.to).join('\n')} name={`부분 코드 ${i + 1} · ${part.from}–${part.to}행`} startLine={part.from} numbered/>{part.text.map((p, j) => <Text key={j}>{p}</Text>)}</div>)}</section>
        <section id="trace">{heading(5)}<Text>{topic.trace.example}</Text>{visualTopics.includes(topic.id) ? <StepVisualizer key={topic.id} topicId={topic.id} code={code}/> : <><StaticDiagram diagram={lesson.diagram}/><Table {...topic.trace} caption={`${topic.title} 작은 입력 추적`}/></>}<Text>{lesson.traceEnd}</Text></section>
        <section id="mistakes">{heading(6)}<h3>입력과 경계 확인</h3>{lesson.boundaries.map((p, i) => <Text key={i}>{p}</Text>)}<div className="mistake-list">{topic.mistakes.map(([wrong, fix]) => <div key={wrong}><h3><Inline>{wrong}</Inline></h3><Text>{fix}</Text></div>)}</div><h3 id="invariant">왜 올바른 답이 남나요?</h3><Text>{topic.invariant}</Text><h3 id="complexity">시간·공간복잡도</h3><Text>{topic.complexity}</Text><h3 id="comparison">비슷한 알고리즘과 선택 기준</h3><Text>{topic.comparison}</Text></section>
        <section id="solutions">{heading(7)}{solutions}</section>
        {children}
    </article>;
}
