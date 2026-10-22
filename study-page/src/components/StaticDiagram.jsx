import React from 'react';

export default function StaticDiagram({ diagram }) {
    if (!diagram) return null;
    return <figure className="static-diagram" tabIndex="0" aria-label="작은 입력의 구조 그림">
        {diagram.nodes ? <svg viewBox={`0 0 620 ${diagram.height || 300}`} role="img" aria-label={diagram.caption}>
            <defs><marker id="direction" viewBox="0 0 10 10" refX="25" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" fill="currentColor"/></marker></defs>
            {diagram.edges.map(([a, b, label], i) => {
                const from = diagram.nodes[a], to = diagram.nodes[b];
                return <g key={i}><line x1={from.x} y1={from.y} x2={to.x} y2={to.y} stroke="currentColor" strokeWidth="1.5" markerEnd={diagram.directed ? "url(#direction)" : undefined}/>{label !== undefined && <text x={(from.x + to.x)/2 + 12} y={(from.y + to.y)/2 - 10} fontSize="18">{label}</text>}</g>;
            })}
            {diagram.nodes.map((n, i) => <g key={i}>{n.range ? <rect x={n.x-57} y={n.y-25} width="114" height="62" rx="4" fill="white" stroke="currentColor"/> : <circle cx={n.x} cy={n.y} r="27" fill="white" stroke="currentColor" strokeWidth="1.5"/>}<text x={n.x} y={n.y + 6} textAnchor="middle" fontSize="20">{n.label ?? i}</text>{n.range && <text x={n.x} y={n.y+27} textAnchor="middle" fontSize="18">{n.range}</text>}</g>)}
        </svg> : diagram.rows.map((row, i) => <div className="diagram-row" key={i}><strong>{row.label}</strong><div className="array-strip">{row.values.map((value, j) => <div className="array-entry" key={j}><span className="index-label">{row.indices?.[j] ?? j}</span><span className="array-cell">{String(value)}</span></div>)}</div></div>)}
        <figcaption>{diagram.caption}{diagram.nodes && <p className="diagram-hint">좁은 화면에서는 그림을 좌우로 스크롤할 수 있습니다.</p>}</figcaption>
    </figure>;
}
