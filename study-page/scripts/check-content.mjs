import assert from 'node:assert/strict';
import { readFile, readdir } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { fileURLToPath } from 'node:url';
import path from 'node:path';
import { mistakeNotes, guides, quickNotes } from '../src/content/reference.js';
const root = fileURLToPath(new URL('../', import.meta.url));
const catalog = JSON.parse(await readFile(path.join(root,'src/content/catalog.json'),'utf8'));
const solutions = JSON.parse(await readFile(path.join(root,'src/data/solutions.json'),'utf8'));
assert.equal(catalog.length,45);
const repository = JSON.parse(await readFile(path.join(root,'data/repository.json'),'utf8'));
const ids = new Set(catalog.map(t=>t.id));
assert.equal(ids.size,45);
assert.equal((await readdir(path.join(root,'templates'))).filter(p=>p.endsWith('.cpp')).length,45);
const usedVariants = new Set();
for (const item of catalog) {
    const data = JSON.parse(await readFile(path.join(root,`src/content/topics/${item.id}.json`),'utf8'));
    assert.equal(data.id,item.id);
    assert.equal(data.summary,item.summary, `${item.id}: catalog summary must match topic`);
    for (const field of ['title','summary','concept','conditions','optimize','steps','variables','invariant','trace','complexity','mistakes','comparison']) assert.ok(data[field]?.length || typeof data[field]==='object', `${item.id}: ${field}`);
    assert.ok(data.conditions.length>=2 && data.steps.length>=3 && data.mistakes.length>=2);
    assert.ok(data.trace.rows.length>=3 && data.trace.rows.every(row=>row.length===3));
    const code = await readFile(path.join(root,`templates/${item.id}.cpp`),'utf8');
    const lesson = data.lesson;
    const overview = data.overview;
    assert.ok(overview && ['purpose','state','saving','templateTitle','templateScope'].every(key => typeof overview[key] === 'string' && overview[key].trim()), `${item.id}: general principles and scoped template`);
    assert.ok(overview.signals.length >= 2 && overview.limits.length >= 1, `${item.id}: applicability`);
    assert.ok(overview.forms.length >= 2 && overview.forms.every(row => row.length === 3), `${item.id}: representative forms`);
    assert.ok(overview.variations.length >= 2 && overview.variations.every(row => row.length === 3), `${item.id}: variation changes`);
    for (const related of overview.related) assert.ok(ids.has(related), `${item.id}: related template link`);
    for (const extra of overview.extraTemplates) {
        assert.ok(/^[a-z0-9-]+$/.test(extra.file) && !usedVariants.has(extra.file), `${item.id}: unique variant source`);
        usedVariants.add(extra.file);
        for (const key of ['title','scope','range','entry','invariant','complexity']) assert.ok(typeof extra[key] === 'string' && extra[key].trim(), `${extra.file}: ${key}`);
        assert.ok(extra.variables.length >= 2 && extra.order.length >= 3 && extra.mistakes.length, `${extra.file}: execution explanation`);
        assert.ok(extra.example.input && extra.example.result && extra.example.rows.length >= 3 && extra.example.rows.every(row => row.length === 3), `${extra.file}: complete small trace`);
        const source = await readFile(path.join(root,`templates/variants/${extra.file}.cpp`),'utf8');
        assert.ok(source.includes('using namespace std;') && !/TODO|\bclass\b|bits\/stdc|size_t|unsigned|static_cast|numeric_limits/.test(source), `${extra.file}: concrete personal-style code`);
        for (const line of source.split('\n')) if (line.trim()) assert.ok(!line.includes('\t') && (line.length - line.trimStart().length) % 4 === 0, `${extra.file}: indentation`);
    }

    assert.ok(lesson && ['problem','idea','entry','range','traceEnd'].every(field => typeof lesson[field] === 'string' && lesson[field].trim()), `${item.id}: required explanations`);
    assert.ok(!/(?<!아)니다|세요|원소 반영|조건 복구|해당 시점|이제 살펴보|중요한 점은/.test(JSON.stringify(data)), `${item.id}: concrete notebook tone`);
    assert.ok(lesson.variables.length >= 2 && lesson.boundaries.length && lesson.traceEnd.trim(), `${item.id}: details`);
    assert.ok(lesson.walkthrough.length >= 3, `${item.id}: walkthrough`);
    const lineCount = code.trimEnd().split('\n').length;
    for (const part of lesson.walkthrough) {
        assert.ok(Number.isInteger(part.from) && part.from >= 1 && part.to >= part.from && part.to <= lineCount, `${item.id}: source range`);
        assert.ok(part.text.length && part.text.every(text => typeof text === 'string' && text.trim()), `${item.id}: execution explanation`);
    }
    if (['sliding-window','monotonic-deque','binary-search'].includes(item.id)) {
        const trace = JSON.parse(await readFile(path.join(root,`src/data/traces/${item.id}.json`),'utf8'));
        assert.equal(trace.sourceHash, createHash('sha256').update(code).digest('hex'), `${item.id}: stale replay; regenerate traces`);
        assert.equal(trace.cases.length,4);
        for (const example of trace.cases) {
            assert.ok(example.steps.length >= 2);
            for (const [i, step] of example.steps.entries()) {
                assert.ok(step.line >= 1 && step.line <= lineCount && code.split('\n')[step.line-1].trim(), `${item.id}: trace line`);
                assert.deepEqual(step.before, i ? example.steps[i-1].after : null, `${item.id}: before/after continuity`);
            }
        }
    } else assert.ok(lesson.diagram?.rows?.length || lesson.diagram?.nodes?.length, `${item.id}: static diagram`);
    assert.ok(lesson.range?.trim(), `${item.id}: bounds and numeric types`);
    assert.ok(!/\b(?:size_t|unsigned|static_cast|numeric_limits)\b|1ULL|__builtin_popcount|auto\s*\[|auto&\s*\[/.test(code), `${item.id}: personal C++ convention`);
    assert.ok(!/for\s*\([^;]*;[^;]*\.size\(\)/.test(code), `${item.id}: cache length as int`);
    assert.ok(!code.replace('using ll = long long;', '').includes('long long'), `${item.id}: use ll alias`);
    assert.ok(!/\barr\b/.test(code), `${item.id}: use nums`);
    for (const line of code.split('\n')) if (line.trim()) assert.ok(!line.includes('\t') && (line.length-line.trimStart().length)%4===0, `${item.id}: four-space indent`);
    if (/const (?:ll|int) INF/.test(code)) assert.ok(/const (?:ll|int) INF = [0-9'][0-9']*(?:LL)?;/.test(code), `${item.id}: explicit integer INF`);
    assert.ok(!/static_cast|numeric_limits|1ULL|__builtin_popcount/.test(JSON.stringify(data)), `${item.id}: stale style explanation`);
    assert.ok(code.includes('using namespace std;'));
    assert.ok(!/bits\/stdc|class\s/.test(code));
    assert.ok(!/추후 추가|준비 중|TODO|lorem ipsum/i.test(JSON.stringify(data)));
}
assert.deepEqual([...usedVariants].sort(), (await readdir(path.join(root,'templates/variants'))).filter(file => file.endsWith('.cpp')).map(file => file.slice(0,-4)).sort(), 'Every concrete variant must be documented');
for (const notes of [mistakeNotes,guides,quickNotes]) {
    assert.ok(!/(?<!아)니다|세요|원소 반영|조건 복구|해당 시점|이제 살펴보|중요한 점은/.test(JSON.stringify(notes)), 'Reference notebook tone');
    assert.equal(new Set(notes.map(x=>x.id)).size,notes.length);
    for (const note of notes) for (const id of note.links || []) assert.ok(ids.has(id), `Broken reference: ${id}`);
}
for (const s of solutions) {
    if (repository.trackedPaths.includes(s.path)) assert.ok(s.githubUrl, `Missing GitHub link: ${s.path}`);
    const original = await readFile(path.resolve(root,'..',s.path),'utf8');
    assert.equal(s.code, original, `Source mismatch: ${s.path}`);
    assert.equal(createHash('sha256').update(s.code).digest('hex'), s.codeHash);
    assert.ok(s.topics.length && s.topics.every(id=>ids.has(id)), `Missing topic: ${s.path}`);
    assert.ok(!/(?<!아)니다|세요/.test([s.verificationNote, s.fileNote].filter(Boolean).join(' ')), `Source-note tone: ${s.path}`);
    if (s.difficulty) assert.ok(s.sourceUrl && s.verifiedAt && s.difficultySource);
    if (s.url) assert.ok(s.verified,`Unverified link: ${s.path}`);
}
console.log(`콘텐츠 ${catalog.length}개 · 실수 노트 ${mistakeNotes.length}개 · 선택 가이드 ${guides.length}개 · 원본 일치 ${solutions.length}개 통과`);

const app = await readFile(path.join(root,'src/main.jsx'),'utf8');
const css = await readFile(path.join(root,'src/style.css'),'utf8');
const copyUi = await readFile(path.join(root,'src/components/CodeBlock.jsx'),'utf8');
assert.ok(!/(?<!아)니다|세요/.test(app + copyUi), 'Shared UI notebook tone');
assert.ok(!/study-theme|setTheme|localStorage|prefers-color-scheme|data-theme/.test(app + css), 'Light-only UI must not contain theme settings');
console.log('설명 45개 · 원본 행 범위 · 시각화 12개 입력의 코드 해시·단계 연속성 · 밝은 화면 전용 확인');

console.log('개인 C++ 컨벤션 · 주제별 입력 범위와 자료형 · 설명/추적 최신화 확인');

console.log(`공통 개념·대표 형태·적용 범위 45개 · 독립 변형 템플릿 ${usedVariants.size}개 · 예제와 코드 연결 확인`);
