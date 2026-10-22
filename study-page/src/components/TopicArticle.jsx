import React from 'react';
import { Inline, Text, Table } from './Reading';
import CodeBlock from './CodeBlock';
import StepVisualizer, { visualTopics } from './StepVisualizer';
import StaticDiagram from './StaticDiagram';
import catalog from '../content/catalog.json';

const titles = Object.fromEntries(catalog.map(topic => [topic.id, topic.title]));
export const sections = [['concept', '공통 개념'], ['forms', '대표 형태'], ['template', '기본 템플릿'], ['trace', '작은 예제'], ['mistakes', '변형과 실수'], ['solutions', '연결된 내 풀이']];

export default function TopicArticle({ topic, code, variantCodes, solutions, children }) {
    const lesson = topic.lesson;
    const overview = topic.overview;
    const lines = code.trimEnd().split('\n');
    function heading(i) {
        const [id, title] = sections[i];
        return <h2><span className="section-index">{String(i + 1).padStart(2, '0')}</span>{title}<a className="heading-link" href={`#${id}`} aria-label={`${title} 바로가기`}>#</a></h2>;
    }
    return <article className="topic-article">
        <section id="concept">{heading(0)}
            <Text>{overview.purpose}</Text><Text>{overview.state}</Text>
            <h3 id="optimize">줄이는 계산</h3><Text>{overview.saving}</Text>
            <div id="conditions"><h3>떠올릴 조건</h3><ul className="body-list">{overview.signals.map(text => <li key={text}><Inline>{text}</Inline></li>)}</ul>
                <h3>적용 범위</h3>{overview.limits.map(text => <Text key={text}>{text}</Text>)}
            </div>
        </section>
        <section id="forms">{heading(1)}
            <Table headers={['형태', '유지할 내용', '달라지는 부분']} rows={overview.forms} caption={`${topic.title} 대표 형태 비교`}/>
            {overview.related.length > 0 && <><p>다른 형태의 전체 코드·선택 기준</p><div className="topic-chips">{overview.related.map(id => <a key={id} href={`/topics/${id}`}>{titles[id]}</a>)}</div></>}
        </section>
        <section id="template">{heading(2)}
            {overview.extraTemplates.length > 0 && <p>형태별 코드는 각각 독립 사용. 해결할 조건에 맞는 코드 선택.</p>}
            <h3>{overview.templateTitle}</h3><Text>{overview.templateScope}</Text><Text>{lesson.range}</Text>
            <CodeBlock code={code} numbered/><Text>{lesson.entry}</Text>
            <div id="variables"><h3>변수·배열</h3><Table headers={['변수 / 배열', '정확한 의미']} rows={lesson.variables} caption={`${topic.title} 변수 정의`}/></div>
            <div id="steps">{lesson.walkthrough.map((part, i) => <div className="walkthrough" key={i}>
                <h3>{i + 1}. {part.title}</h3><CodeBlock code={lines.slice(part.from - 1, part.to).join('\n')} name={`부분 코드 ${i + 1} · ${part.from}–${part.to}행`} startLine={part.from} numbered/>
                {part.text.map((text, j) => <Text key={j}>{text}</Text>)}
            </div>)}</div>
            <h3 id="invariant">이 템플릿의 불변식</h3><Text>{topic.invariant}</Text>
            {overview.extraTemplates.map(extra => <div className="variant-template" id={`template-${extra.file}`} data-variant={extra.file} key={extra.file}>
                <h3>{extra.title}</h3><Text>{extra.scope}</Text><Text>{extra.range}</Text>
                <CodeBlock code={variantCodes[`../templates/variants/${extra.file}.cpp`]} name={`C++17 · ${extra.title}`} numbered/><Text>{extra.entry}</Text>
                <Table headers={['변수 / 배열', '정확한 의미']} rows={extra.variables} caption={`${extra.title} 변수 정의`}/>
                <ol className="body-list">{extra.order.map(text => <li key={text}><Inline>{text}</Inline></li>)}</ol><Text>{extra.invariant}</Text>
            </div>)}
        </section>
        <section id="trace">{heading(3)}
            <h3>{overview.templateTitle}</h3><Text>{topic.trace.example}</Text>
            {visualTopics.includes(topic.id) ? <StepVisualizer key={topic.id} topicId={topic.id} code={code}/> : <><StaticDiagram diagram={lesson.diagram}/><Table {...topic.trace} caption={`${topic.title} 작은 입력 추적`}/></>}
            <Text>{lesson.traceEnd}</Text>
            {overview.extraTemplates.map(extra => <div className="small-example" data-example={extra.file} key={extra.file}>
                <h3>{extra.title}</h3><Text>{extra.example.input}</Text>
                <Table headers={extra.example.headers} rows={extra.example.rows} caption={`${extra.title} 작은 입력 추적`}/><Text>{extra.example.result}</Text>
            </div>)}
        </section>
        <section id="mistakes">{heading(4)}
            <Table headers={['바뀌는 조건', '수정할 부분', '주의']} rows={overview.variations} caption={`${topic.title} 변형별 변경점`}/>
            <h3>{overview.templateTitle}의 경계·반례</h3>{lesson.boundaries.map((text, i) => <Text key={i}>{text}</Text>)}
            <div className="mistake-list">{topic.mistakes.map(([wrong, fix]) => <div key={wrong}><h3><Inline>{wrong}</Inline></h3><Text>{fix}</Text></div>)}</div>
            {overview.extraTemplates.map(extra => <div key={extra.file}><h3>{extra.title}의 실수</h3><ul className="body-list">{extra.mistakes.map(text => <li key={text}><Inline>{text}</Inline></li>)}</ul></div>)}
            <h3 id="complexity">템플릿별 복잡도</h3><Text>{`${overview.templateTitle}: ${topic.complexity}`}</Text>
            {overview.extraTemplates.length > 0 && <ul className="body-list">{overview.extraTemplates.map(extra => <li key={extra.file}><Inline>{`${extra.title}: ${extra.complexity}`}</Inline></li>)}</ul>}
            <h3 id="comparison">다른 알고리즘과 선택 기준</h3><Text>{topic.comparison}</Text>
        </section>
        <section id="solutions">{heading(5)}{solutions}</section>
        {children}
    </article>;
}
