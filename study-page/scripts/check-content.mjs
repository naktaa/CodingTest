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
for (const item of catalog) {
    const data = JSON.parse(await readFile(path.join(root,`src/content/topics/${item.id}.json`),'utf8'));
    assert.equal(data.id,item.id);
    for (const field of ['title','summary','concept','conditions','optimize','steps','variables','invariant','trace','complexity','mistakes','comparison']) assert.ok(data[field]?.length || typeof data[field]==='object', `${item.id}: ${field}`);
    assert.ok(data.conditions.length>=2 && data.steps.length>=3 && data.mistakes.length>=2);
    assert.ok(data.trace.rows.length>=3 && data.trace.rows.every(row=>row.length===3));
    const code = await readFile(path.join(root,`templates/${item.id}.cpp`),'utf8');
    assert.ok(code.includes('using namespace std;'));
    assert.ok(!/bits\/stdc|class\s/.test(code));
    assert.ok(!/추후 추가|준비 중|TODO|lorem ipsum/i.test(JSON.stringify(data)));
}
for (const notes of [mistakeNotes,guides,quickNotes]) {
    assert.equal(new Set(notes.map(x=>x.id)).size,notes.length);
    for (const note of notes) for (const id of note.links || []) assert.ok(ids.has(id), `Broken reference: ${id}`);
}
for (const s of solutions) {
    if (repository.trackedPaths.includes(s.path)) assert.ok(s.githubUrl, `Missing GitHub link: ${s.path}`);
    const original = await readFile(path.resolve(root,'..',s.path),'utf8');
    assert.equal(s.code, original, `Source mismatch: ${s.path}`);
    assert.equal(createHash('sha256').update(s.code).digest('hex'), s.codeHash);
    assert.ok(s.topics.length && s.topics.every(id=>ids.has(id)), `Missing topic: ${s.path}`);
    if (s.difficulty) assert.ok(s.sourceUrl && s.verifiedAt && s.difficultySource);
    if (s.url) assert.ok(s.verified,`Unverified link: ${s.path}`);
}
console.log(`콘텐츠 ${catalog.length}개 · 실수 노트 ${mistakeNotes.length}개 · 선택 가이드 ${guides.length}개 · 원본 일치 ${solutions.length}개 통과`);
