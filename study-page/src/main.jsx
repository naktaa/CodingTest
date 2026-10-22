import React, { useEffect, useRef, useState } from 'react';
import { createRoot } from 'react-dom/client';
import CodeBlock from './components/CodeBlock';
import { Inline, Text, Table } from './components/Reading';
import TopicArticle, { sections } from './components/TopicArticle';
import catalog from './content/catalog.json';
import solutions from './data/solutions.json';
import { mistakeNotes, guides, quickNotes } from './content/reference.js';
import '@fontsource-variable/noto-sans-kr';
import './style.css';

const modules = import.meta.glob('./content/topics/*.json', { eager: true, import: 'default' });
const templates = import.meta.glob('../templates/*.cpp', { eager: true, query: '?raw', import: 'default' });
const variantCodes = import.meta.glob('../templates/variants/*.cpp', { eager: true, query: '?raw', import: 'default' });
const topics = Object.fromEntries(Object.values(modules).map(t => [t.id, t]));
const normalize = value => value.normalize('NFKC').toLowerCase().replace(/\s+/g, '');
function readRoute() { return { path: decodeURI(location.pathname), query: new URLSearchParams(location.search).get('q') || '', hash: location.hash }; }
function Icon({ name, size = 18 }) {
    const paths = { search: <><circle cx="10.5" cy="10.5" r="6.5"/><path d="m16 16 4 4"/></>, book: <><path d="M12 5C8 2 3 3 3 3v16s5-1 9 2c4-3 9-2 9-2V3s-5-1-9 2Z"/><path d="M12 5v16"/></>, arrow: <path d="m9 5 7 7-7 7"/>, external: <><path d="M14 3h7v7M21 3 10 14M10 3H4v17h17v-6"/></>, copy: <><rect x="8" y="8" width="12" height="13" rx="2"/><path d="M16 8V3H3v13h5"/></>, menu: <path d="M3 6h18M3 12h18M3 18h18"/>, close: <path d="m5 5 14 14M5 19 19 5"/>, check: <path d="m5 12 4 4L19 6"/> };
    return <svg width={size} height={size} viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="1.6" strokeLinecap="round" strokeLinejoin="round" aria-hidden="true">{paths[name] || paths.book}</svg>;
}
function External({ href, children, ...props }) { return <a href={href} target="_blank" rel="noreferrer" {...props}>{children}<Icon name="external" size={13}/><span className="sr-only"> (새 탭)</span></a>; }
function Difficulty({ solution }) {
    const label = solution.difficulty || '난이도 미확인';
    const tone = /Gold|Medium|Lv\. 2/.test(label) ? 'gold' : /Platinum|Diamond|Hard|Lv\. [34]/.test(label) ? 'purple' : /Silver/.test(label) ? 'silver' : 'green';
    return <span className={`difficulty ${tone}`} title={`${solution.difficultySource || '조회 제한'}${solution.snapshot ? ' · 공개 목록에 기록된 등급' : ''}`}>{label}{solution.snapshot && <span aria-label="기록된 등급">*</span>}</span>;
}
function SolutionList({ items, limit }) {
    const list = limit ? items.slice(0, limit) : items;
    return <div className="solution-list">{list.map(s => <div className="solution-row" key={s.path}><div><span className="platform">{s.platform === 'Baekjoon' ? '백준' : s.platform === 'Programmers' ? '프로그래머스' : s.platform === 'JUNGOL' ? '정올' : 'LeetCode'}{s.platform !== 'Programmers' ? ` · ${s.id}` : ''}</span><a className="solution-title" href={`/solutions/${encodeURIComponent(s.path)}`}>{s.title}<Icon name="arrow" size={14}/></a>{s.fileNote && <small className="file-note">파일명 번호 확인 항목</small>}</div><div className="solution-links"><Difficulty solution={s}/>{s.url && <External href={s.url}>문제</External>}<a className="source-link" href={`/solutions/${encodeURIComponent(s.path)}`}>내 코드</a></div></div>)}</div>;
}
function App() {
    const [route, setRoute] = useState(readRoute);
    const [activeSection, setActiveSection] = useState('concept');
    const searchRef = useRef(); const dialogRef = useRef(); const headingRef = useRef(); const firstPage = useRef(true);
    const topicId = route.path.startsWith('/topics/') ? route.path.slice(8) : '';
    const topic = topics[topicId];
    const solution = route.path.startsWith('/solutions/') ? solutions.find(s => s.path === decodeURIComponent(route.path.slice(11))) : null;
    const reference = route.path === '/mistakes' ? 'mistakes' : route.path === '/guide' ? 'guide' : route.path === '/quick' ? 'quick' : null;
    const isSearch = route.path === '/search';
    const isLibrary = route.path === '/solutions';
    const isHome = route.path === '/';
    const pageTitle = topic?.title || solution?.title || (reference === 'mistakes' ? '순서와 경계 실수 노트' : reference === 'guide' ? '어떤 알고리즘을 쓸까?' : reference === 'quick' ? '시험 직전 요약' : isSearch ? '노트 검색' : isLibrary ? '내 풀이 모아보기' : isHome ? '알고리즘 공부 노트' : '문서 없음');

    useEffect(() => {
        const listener = () => setRoute(readRoute());
        const keyboard = e => { if ((e.ctrlKey || e.metaKey) && e.key.toLowerCase() === 'k') { e.preventDefault(); searchRef.current?.focus(); } };
        addEventListener('popstate', listener); addEventListener('keydown', keyboard);
        return () => { removeEventListener('popstate', listener); removeEventListener('keydown', keyboard); };
    }, []);
    useEffect(() => {
        document.title = `${pageTitle} · naktaa 알고리즘 노트`;
        dialogRef.current?.close();
        if (route.hash) {
            const id = decodeURIComponent(route.hash.slice(1));
            requestAnimationFrame(() => document.getElementById(id)?.scrollIntoView());
        } else { window.scrollTo({ top: 0, behavior: 'instant' }); }
        if (!isSearch && !firstPage.current) headingRef.current?.focus({ preventScroll: true });
        firstPage.current = false;
    }, [route.path, pageTitle]);
    useEffect(() => {
        if (!topic && !reference) return;
        const observer = new IntersectionObserver(entries => {
            entries.forEach(entry => { if (entry.isIntersecting) setActiveSection(entry.target.id); });
        }, { rootMargin: '-90px 0px -60% 0px' });
        document.querySelectorAll('article section[id]').forEach(el => observer.observe(el));
        return () => observer.disconnect();
    }, [topic, reference]);
    function navigate(href, replace = false) {
        const url = new URL(href, location.origin);
        history[replace ? 'replaceState' : 'pushState']({}, '', url);
        setRoute(readRoute());
        if (url.hash) requestAnimationFrame(() => {
            const target = document.getElementById(decodeURIComponent(url.hash.slice(1)));
            target?.scrollIntoView({ behavior: 'smooth' });
            if (url.hash === '#main') target?.focus({ preventScroll: true });
        });
    }
    function onLink(e) {
        const anchor = e.target.closest('a');
        if (!anchor || e.defaultPrevented || e.button !== 0 || e.metaKey || e.ctrlKey || e.shiftKey || e.altKey || anchor.target || anchor.hasAttribute('download')) return;
        const url = new URL(anchor.href);
        if (url.origin === location.origin) { e.preventDefault(); navigate(url.href); }
    }
    const q = normalize(route.query);
    const words = q.split(/[、,]+/).filter(Boolean);
    const match = text => words.every(word => normalize(text).includes(word));
    const resultTopics = q ? catalog.filter(t => match(JSON.stringify(topics[t.id]))) : [];
    const resultSolutions = q ? solutions.filter(s => /^\d+$/.test(q) ? s.id === q : match(`${s.title} ${s.id} ${s.path} ${s.difficulty || ''} ${s.topics.map(id => topics[id]?.title || id).join(' ')}`)) : [];
    const resultNotes = q ? mistakeNotes.filter(n => match(JSON.stringify(n))) : [];
    const related = topic ? solutions.filter(s => s.topics.includes(topic.id)) : [];
    const toc = topic ? sections : reference === 'mistakes' ? mistakeNotes.map(n => [n.id, n.title]) : reference === 'guide' ? guides.map(n => [n.id, n.title]) : reference === 'quick' ? quickNotes.map(n => [n.id, n.title]) : [];
    const index = topic ? catalog.findIndex(t => t.id === topic.id) : -1;
    function nav() {
        return <><div className="sidebar-top"><span className="eyebrow">MY STUDY SPACE</span><p>읽고, 이해하고,<br/>내 코드로 확인하기.</p></div><nav aria-label="학습 문서"><div className="nav-shortcuts"><a href="/" aria-current={isHome ? 'page' : undefined}><Icon name="book" size={16}/>노트 첫 페이지</a><a href="/guide" aria-current={reference === 'guide' ? 'page' : undefined}>알고리즘 선택 가이드</a><a href="/mistakes" aria-current={reference === 'mistakes' ? 'page' : undefined}>순서와 경계 실수 노트<span className="small-dot"/></a><a href="/quick" aria-current={reference === 'quick' ? 'page' : undefined}>시험 직전 요약</a><a href="/solutions" aria-current={isLibrary || solution ? 'page' : undefined}>내 풀이 모아보기 <span className="nav-count">{solutions.length}</span></a></div>{['기본','핵심','확장'].map((group, gi) => <details className="nav-group" key={group} open><summary><span>{String(gi+1).padStart(2,'0')}<b>{group}</b></span><Icon name="arrow" size={13}/></summary><div>{catalog.filter(t => t.group === group).map(t => <a key={t.id} href={`/topics/${t.id}`} aria-current={topicId === t.id ? 'page' : undefined}>{t.title}</a>)}</div></details>)}</nav><div className="sidebar-bottom"><span className="status-dot"/>C++17 · 개인 공부 기록<External href="https://github.com/naktaa/CodingTest">naktaa / CodingTest</External></div></>;
    }
    return <div onClick={onLink}><a className="skip-link" href="#main">본문으로 건너뛰기</a><header className="topbar"><a className="brand" href="/" aria-label="알고리즘 노트 첫 페이지"><span className="brand-mark"><Icon name="book" size={22}/></span><span>알고리즘 <strong>노트</strong><small>naktaa’s study page</small></span></a><div className="search-box"><Icon name="search" size={17}/><input ref={searchRef} aria-label="알고리즘, 문제, 표현 검색" placeholder="유형, 문제 또는 ‘연속된 구간’ 검색" value={isSearch ? route.query : ''} onChange={e => { const value = e.target.value; navigate(`/search${value ? `?q=${encodeURIComponent(value)}` : ''}`, isSearch); }}/><kbd>Ctrl K</kbd>{isSearch && route.query && <button aria-label="검색어 지우기" onClick={() => navigate('/search', true)}><Icon name="close" size={14}/></button>}</div><div className="header-actions"><span className="header-label">C++17</span><button className="icon-button mobile-menu" aria-label="학습 메뉴 열기" aria-haspopup="dialog" onClick={() => dialogRef.current?.showModal()}><Icon name="menu"/></button></div></header><aside className="sidebar">{nav()}</aside><dialog className="mobile-drawer" ref={dialogRef} aria-label="학습 메뉴"><button className="drawer-close icon-button" aria-label="학습 메뉴 닫기" onClick={() => dialogRef.current.close()}><Icon name="close"/></button>{nav()}</dialog><div className={`workspace ${toc.length ? '' : 'no-toc'}`}><main id="main" tabIndex="-1"><div className="breadcrumb"><a href="/">공부 노트</a><Icon name="arrow" size={12}/><span>{topic ? topic.group : solution || isLibrary ? '내 풀이' : '나의 알고리즘 서재'}</span>{topic && <><Icon name="arrow" size={12}/><span>{topic.title}</span></>}</div>
        {isHome ? <><div className="page-heading home-heading"><div className="eyebrow">CODING TEST · STUDY NOTES</div><h1 ref={headingRef} tabIndex="-1">알고리즘을 고르는 기준,<br/><em>코드를 쓰는 순서.</em></h1><p>조건에서 풀이를 찾고, 작은 예제로 순서를 따라가고,<br className="desktop-br"/> 내가 푼 코드로 다시 확인하는 개인 공부 노트.</p><div className="home-meta"><span>{catalog.length}개의 개념 노트</span><span>{solutions.length}개의 내 풀이</span><span>C++17</span></div></div><div className="start-note"><span className="note-symbol">↳</span><div><strong>헷갈리는 부분부터 다시 읽기.</strong><p>한화비전·현대오토에버 코테 준비용 개인 노트.<br/>기초부터 확장까지 문제 조건으로 유형 구분. 기업별 출제 빈도는 단정하지 않기.</p></div></div><div className="section-label"><h2>공부의 출발점</h2><span>HOW TO READ</span></div><div className="entry-grid">{[['/guide','01','조건을 보고 유형 고르기','누적합과 차분, BFS와 다익스트라. 문제 조건에 따른 선택 기준 비교.'],['/mistakes','02','순서와 경계 다시 보기','if와 while, +1 하나, 마지막 묶음. 자주 틀리는 순서를 반례로 확인.'],['/quick','03','시험 직전 빠르게 읽기','입력 크기, 초기화, 방문 시점. 제출 전 핵심 순서 점검.']].map(([href,num,title,desc]) => <a className="entry-card" key={href} href={href}><span className="entry-number">{num}<Icon name="arrow" size={15}/></span><h3>{title}</h3><p>{desc}</p></a>)}</div><div className="section-label"><h2>유형별 노트</h2><span>THE NOTEBOOK</span></div><div className="topic-directory">{['기본','핵심','확장'].map((g,i) => <section className="directory-group" key={g}><div><span className="directory-num">0{i+1}</span><h3>{g}</h3><p>{['코드를 읽고 쓰는 기반','풀이의 중심이 되는 패턴','조건이 더해질 때의 도구'][i]}</p></div><div className="topic-chips">{catalog.filter(t => t.group === g).map(t => <a key={t.id} href={`/topics/${t.id}`}>{t.title}<Icon name="arrow" size={11}/></a>)}</div></section>)}</div><div className="section-label"><h2>내 코드와 함께 읽기</h2><a href="/solutions">전체 풀이 보기 →</a></div><SolutionList items={solutions.filter(s => s.platform === 'LeetCode').slice(0,4)}/></> : <><div className="page-heading"><span className="eyebrow">{topic ? `${topic.group} / ALGORITHM NOTE` : solution ? 'MY SOLUTION / C++' : reference ? 'REFERENCE NOTE' : isSearch ? 'SEARCH THE NOTEBOOK' : 'MY SOLUTIONS'}</span><h1 ref={headingRef} tabIndex="-1">{pageTitle}</h1>{topic && <><p>{topic.summary}</p><div className="topic-meta"><span>C++17</span><span>기본 함수 템플릿</span><a href="#solutions">연결된 풀이 {related.length}개 ↓</a></div></>}{isLibrary && <p>레포의 풀이를 알고리즘별로 연결. 파일 보유 여부와 정답 통과 여부는 별개.</p>}</div>
        {toc.length > 0 && <details className="inline-toc"><summary>이 문서의 목차</summary><nav onClick={e => { if (e.target.closest('a')) e.currentTarget.closest('details').open = false; }}>{toc.map(([id,label]) => <a key={id} href={`#${id}`}>{label}</a>)}</nav></details>}
        {topic && <TopicArticle key={topic.id} topic={topic} code={templates[`../templates/${topic.id}.cpp`]} variantCodes={variantCodes} solutions={<>{related.length ? <SolutionList items={related}/> : <div className="empty-related"><p>현재 레포에서 이 주제로 분류한 풀이 파일 없음.</p><a href="/guide">선택 가이드에서 관련 유형 함께 보기 →</a></div>}<p className="source-caption">백준 난이도는 공개 목록·제출 기록 기준. 각 풀이에 출처와 확인 날짜 표시.</p></>}><div className="page-turn">{index > 0 && <a href={`/topics/${catalog[index-1].id}`}><small>← 이전 노트</small>{catalog[index-1].title}</a>}{index < catalog.length-1 && <a href={`/topics/${catalog[index+1].id}`}><small>다음 노트 →</small>{catalog[index+1].title}</a>}</div></TopicArticle>}
        {solution && <article><div className="solution-meta"><Difficulty solution={solution}/><span>{solution.platform} · {solution.id}</span>{solution.url && <External href={solution.url}>문제 원문</External>}{solution.githubUrl && <External href={solution.githubUrl}>GitHub 원본</External>}</div><div className="topic-chips related-chips">{solution.topics.map(id => <a key={id} href={`/topics/${id}`}>{topics[id]?.title}<Icon name="arrow" size={12}/></a>)}</div>{solution.fileNote && <div className="reading-note">{solution.fileNote}</div>}<p className="muted file-path">{solution.path}</p><CodeBlock key={solution.path} name="C++ · 내 로컬 풀이 원본" code={solution.code}/><div className="source-details"><h2>문제 정보 출처</h2><p>{solution.verificationNote || `문제 원문의 제목·난이도 대조. 확인 날짜: ${solution.verifiedAt || '미확인'}.`}</p>{solution.sourceUrl && <External href={solution.sourceUrl}>{solution.difficultySource} · {solution.verifiedAt}</External>}<p>현재 로컬 파일의 코드. 로컬 수정이 있으면 GitHub 원본과 차이 가능.{solution.localOnly ? ' 아직 Git에 등록하지 않은 로컬 파일.' : ''}</p></div></article>}
        {reference && <article>{(reference === 'mistakes' ? mistakeNotes : reference === 'guide' ? guides : quickNotes).map((n,i) => <section id={n.id} key={n.id}><h2><span className="section-index">{String(i+1).padStart(2,'0')}</span>{n.title}<a className="heading-link" href={`#${n.id}`} aria-label={`${n.title} 바로가기`}>#</a></h2>{n.text && <Text>{n.text}</Text>}{n.rows && <Table headers={n.headers} rows={n.rows}/ >}{n.points && <ul className="body-list">{n.points.map(s => <li key={s}><Inline>{s}</Inline></li>)}</ul>}{n.links && <div className="topic-chips">{n.links.map(id => <a key={id} href={`/topics/${id}`}>{topics[id]?.title || id}<Icon name="arrow" size={12}/></a>)}</div>}</section>)}</article>}
        {isSearch && <><p className="search-summary" role="status">{q ? `‘${route.query}’ 검색 결과 · 개념 ${resultTopics.length}개 / 실수 노트 ${resultNotes.length}개 / 풀이 ${resultSolutions.length}개` : '알고리즘·문제 번호·문제 표현으로 검색.'}</p>{q && !resultTopics.length && !resultNotes.length && !resultSolutions.length && <div className="empty-state"><Icon name="search" size={28}/><h2>일치하는 노트 없음.</h2><p>‘중복 없는’, ‘최소 이동’, ‘구간 합’처럼 문제 조건으로 다시 검색.</p></div>}{resultTopics.length > 0 && <><h2 className="result-heading">개념 노트</h2><div className="search-results">{resultTopics.map(t => <a key={t.id} href={`/topics/${t.id}`}><span>{t.group}</span><h3>{t.title}<Icon name="arrow" size={15}/></h3><p>{t.summary}</p><small>{t.keywords.slice(0,5).join(' · ')}</small></a>)}</div></>}{resultNotes.length > 0 && <><h2 className="result-heading">실수 노트</h2><div className="search-results">{resultNotes.map(n => <a key={n.id} href={`/mistakes#${n.id}`}><h3>{n.title}<Icon name="arrow" size={15}/></h3><p>{n.text}</p></a>)}</div></>}{resultSolutions.length > 0 && <><h2 className="result-heading">내 풀이</h2><SolutionList items={resultSolutions}/></>}</>}
        {isLibrary && <SolutionLibrary/>}
        {!topic && !solution && !reference && !isSearch && !isLibrary && !isHome && <div className="empty-state"><p>주소 확인 후 다시 이동하거나 검색으로 문서 찾기.</p><a href="/">노트 첫 페이지로 →</a></div>}
        </>}
        <footer><span>naktaa’s algorithm notebook</span><span>조건 → 순서 → 검증</span></footer></main>{toc.length > 0 && <aside className="toc" aria-label="이 문서의 목차"><span className="eyebrow">ON THIS PAGE</span><nav>{toc.map(([id,label]) => <a key={id} href={`#${id}`} aria-current={activeSection === id ? 'location' : undefined}>{label}</a>)}</nav><a className="back-top" href="#main">맨 위로 ↑</a><p>작은 입력으로<br/>실행 순서 확인.</p></aside>}</div></div>;
}
function SolutionLibrary() {
    const [platform,setPlatform] = useState('전체');
    const [type,setType] = useState('전체');
    const [query,setQuery] = useState('');
    const list = solutions.filter(s => (platform === '전체' || s.platform === platform) && (type === '전체' || s.topics.includes(type)) && normalize(`${s.title}${s.id}${s.difficulty || ''}`).includes(normalize(query)));
    return <><div className="library-filters"><label>플랫폼<select aria-label="플랫폼" value={platform} onChange={e=>setPlatform(e.target.value)}>{['전체','Baekjoon','LeetCode','Programmers','JUNGOL'].map(x=><option key={x}>{x}</option>)}</select></label><label>알고리즘<select aria-label="알고리즘" value={type} onChange={e=>setType(e.target.value)}><option value="전체">전체</option>{catalog.map(t=><option key={t.id} value={t.id}>{t.title}</option>)}</select></label><label>문제 찾기<input placeholder="이름, 번호, 난이도" value={query} onChange={e=>setQuery(e.target.value)}/></label></div><p className="muted" role="status">{list.length}개 풀이 · 난이도는 기록된 출처 기준. 미확인 정보는 추정하지 않기.</p>{list.length ? <SolutionList items={list}/> : <div className="empty-state">조건에 맞는 풀이 없음.</div>}<p className="source-caption">* solved.ac 직접 조회 제한으로 백준 등급은 공개 목록·제출 기록 기준. 각 풀이에 출처 표시.</p></>;
}

createRoot(document.getElementById('root')).render(<App/>);
