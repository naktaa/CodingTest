import React from 'react';

export function Inline({ children }) {
    return String(children).split(/(`[^`]+`)/g).map((part, index) =>
        part.startsWith('`') ? <code key={index}>{part.slice(1, -1)}</code> : part
    );
}

export function Text({ children }) {
    return <p><Inline>{children}</Inline></p>;
}

export function Table({ headers, rows, caption }) {
    return <div className="table-wrap" tabIndex="0" role="region" aria-label={caption || headers.join(', ')}>
        <table>
            {caption && <caption className="sr-only">{caption}</caption>}
            <thead><tr>{headers.map(header => <th key={header} scope="col">{header}</th>)}</tr></thead>
            <tbody>{rows.map((row, i) => <tr key={i}>{row.map((cell, j) =>
                <td key={j}><Inline>{cell}</Inline></td>
            )}</tr>)}</tbody>
        </table>
    </div>;
}
