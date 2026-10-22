import React, { useEffect, useMemo, useRef, useState } from 'react';
import Prism from 'prismjs';
import 'prismjs/components/prism-clike';
import 'prismjs/components/prism-c';
import 'prismjs/components/prism-cpp';

export default function CodeBlock({ code, name = 'C++17 · 전체 템플릿', startLine = 1, activeLine, numbered = false }) {
    const [copied, setCopied] = useState(false);
    const [copyError, setCopyError] = useState('');
    const timer = useRef();
    const normalized = code.replace(/\r\n/g, '\n');
    const html = useMemo(() => Prism.highlight(normalized, Prism.languages.cpp, 'cpp'), [normalized]);
    const lineCount = normalized.replace(/\n$/, '').split('\n').length;
    useEffect(() => () => clearTimeout(timer.current), []);

    async function copy() {
        try {
            await navigator.clipboard.writeText(code);
            setCopied(true);
            setCopyError('');
            clearTimeout(timer.current);
            timer.current = setTimeout(() => setCopied(false), 1800);
        } catch {
            setCopyError('복사할 수 없습니다. 코드 텍스트를 선택해 복사해 주세요.');
        }
    }

    return <div className="code-block" data-active-line={activeLine || undefined}>
        <div className="code-bar">
            <span>{name}{activeLine ? ` · ${activeLine}행 실행` : ''}</span>
            <button type="button" onClick={copy} aria-label={`${name} 코드 복사`}>{copied ? '복사 완료' : '복사'}</button>
        </div>
        <div className={`code-body ${numbered ? 'numbered' : ''}`}>
            {activeLine && <div className="execution-marker" aria-hidden="true"
                style={{ top: `calc(20px + ${activeLine - startLine} * 1.75em)` }}/ >}
            {numbered && <div className="line-numbers" aria-hidden="true">
                {Array.from({ length: lineCount }, (_, i) => <span key={i}>{startLine + i}</span>)}
            </div>}
            <pre tabIndex="0" aria-label={name}><code className="language-cpp" dangerouslySetInnerHTML={{ __html: html }}/></pre>
        </div>
        <span className={copyError ? 'copy-error' : 'sr-only'} role="status">{copied ? '코드를 복사했습니다.' : copyError}</span>
    </div>;
}
