import { test, expect } from '@playwright/test';
import fs from 'node:fs/promises';
import catalog from '../src/content/catalog.json' with { type: 'json' };
import solutions from '../src/data/solutions.json' with { type: 'json' };
const template = async id => fs.readFile(new URL(`../templates/${id}.cpp`, import.meta.url),'utf8');

test('첫 페이지의 전체 목차와 로컬 한글 폰트', async ({page}) => {
    const errors=[]; const remote=[];
    page.on('pageerror',e=>errors.push(e.message));
    page.on('request',r=>{if(!r.url().startsWith('http://127.0.0.1')&&!r.url().startsWith('data:'))remote.push(r.url());});
    await page.goto('/');
    await expect(page.locator('h1')).toContainText('알고리즘을 고르는 기준');
    await expect(page.locator('.topic-directory a')).toHaveCount(45);
    await expect(page.locator('.home-meta')).toContainText('211');
    await page.evaluate(()=>document.fonts.ready);
    expect(await page.evaluate(()=>document.fonts.check('14px "Noto Sans KR Variable"'))).toBe(true);
    expect(await page.evaluate(()=>document.documentElement.scrollWidth<=innerWidth)).toBe(true);
    expect(errors).toEqual([]); expect(remote).toEqual([]);
});

test('45개 주제의 본문·추적표·원본 템플릿·목차', async ({page}) => {
    test.setTimeout(90000);
    for(const topic of catalog){
        await page.goto(`/topics/${topic.id}`);
        await expect(page.locator('h1')).toHaveText(topic.title);
        await expect(page.locator('article section')).toHaveCount(10);
        await expect(page.locator('#trace tbody tr')).not.toHaveCount(0);
        expect(await page.locator('.code-block pre code').textContent()).toBe(await template(topic.id));
        expect(await page.locator('pre').evaluate(el=>el.scrollHeight<=el.clientHeight+2)).toBe(true);
        await expect(page.locator('.toc nav a')).toHaveCount(10);
    }
});

test('문제 표현과 문제 번호 검색', async ({page}) => {
    await page.goto('/');
    const search=page.getByRole('textbox',{name:'알고리즘, 문제, 표현 검색'});
    await search.fill('중복 없는');
    await expect(page.locator('.search-results a[href="/topics/sliding-window"]')).toBeVisible();
    await expect(page).toHaveURL(/search\?q=/);
    await page.reload();
    await expect(search).toHaveValue('중복 없는');
    await search.fill('739');
    await expect(page.locator('.solution-title')).toHaveText('Daily Temperatures');
    await expect(page.locator('.solution-links .difficulty')).toHaveText('Medium');
});

test('빈 검색·결과 없음·Ctrl K', async ({page}) => {
    await page.goto('/search');
    await expect(page.locator('.search-summary')).toContainText('입력하세요');
    await page.keyboard.press('Control+k');
    await expect(page.getByRole('textbox',{name:'알고리즘, 문제, 표현 검색'})).toBeFocused();
    await page.keyboard.type('zzzz-no-match-999');
    await expect(page.locator('.empty-state')).toContainText('찾지 못했습니다');
    await page.getByRole('button',{name:'검색어 지우기'}).click();
    await expect(page.locator('.search-summary')).toContainText('입력하세요');
});

test('새로고침·뒤로·앞으로·목차 주소', async ({page}) => {
    await page.goto('/topics/bfs');
    await page.locator('.sidebar a[href="/topics/lca"]').click();
    await expect(page.locator('h1')).toContainText('LCA');
    await page.reload();
    await expect(page.locator('h1')).toContainText('LCA');
    await page.goBack();
    await expect(page.locator('h1')).toHaveText('BFS');
    await page.goForward();
    await expect(page.locator('h1')).toContainText('LCA');
    await page.locator('.toc a[href="#trace"]').click();
    await expect(page).toHaveURL(/#trace$/);
    await page.reload();
    await expect(page.locator('#trace')).toBeInViewport();
});

test('테마 저장·복원과 저장 불가 환경', async ({page,context}) => {
    await page.goto('/topics/prefix');
    await page.getByRole('button',{name:'어두운 테마로 전환'}).click();
    await expect(page.locator('html')).toHaveAttribute('data-theme','dark');
    expect(await page.evaluate(()=>getComputedStyle(document.documentElement).backgroundColor)).toBe('rgb(23, 29, 26)');
    expect(await page.evaluate(()=>getComputedStyle(document.body).color)).toBe('rgb(209, 217, 209)');
    await page.reload();
    await expect(page.locator('html')).toHaveAttribute('data-theme','dark');
    expect(await page.evaluate(()=>Object.keys(localStorage))).toEqual(['study-theme']);
    await context.clearCookies();
    await page.addInitScript(()=>{Object.defineProperty(window,'localStorage',{get(){throw new Error('blocked');}});});
    await page.reload();
    await expect(page.locator('h1')).toHaveText('누적합');
});

test('복사한 템플릿이 원본과 동일', async ({page,context}) => {
    await context.grantPermissions(['clipboard-read','clipboard-write']);
    await page.goto('/topics/segment-tree');
    await page.getByRole('button',{name:'C++17 · 기본 함수 코드 복사'}).click();
    expect(await page.evaluate(()=>navigator.clipboard.readText())).toBe(await template('segment-tree'));
    await expect(page.getByRole('status')).toContainText('복사했습니다');
});

test('원본 풀이의 코드·링크·난이도', async ({page}) => {
    const solution=solutions.find(s=>s.platform==='LeetCode'&&s.id==='239');
    await page.goto(`/solutions/${encodeURIComponent(solution.path)}`);
    expect(await page.locator('.code-block pre code').textContent()).toBe(solution.code.replace(/\r\n/g,'\n'));
    await expect(page.locator('.solution-meta .difficulty')).toHaveText('Hard');
    await expect(page.getByRole('link',{name:/문제 원문/})).toHaveAttribute('href',solution.url);
    await expect(page.getByRole('link',{name:/GitHub 원본/})).toHaveAttribute('href',solution.githubUrl);
    await page.reload();await expect(page.locator('h1')).toHaveText(solution.title);
});

test('백준 기록의 출처와 파일명 번호 불일치 표시', async ({page}) => {
    const solution=solutions.find(s=>s.platform==='Baekjoon'&&s.id==='1753');
    await page.goto(`/solutions/${encodeURIComponent(solution.path)}`);
    await expect(page.locator('.difficulty')).toContainText('Gold');
    await expect(page.locator('.source-details')).toContainText('기록');
    const mismatch=solutions.find(s=>s.fileNote);
    await page.goto(`/solutions/${encodeURIComponent(mismatch.path)}`);
    await expect(page.locator('.reading-note')).toHaveText(mismatch.fileNote);
});

test('내 풀이 플랫폼·유형·난이도 필터', async ({page}) => {
    await page.goto('/solutions');
    await page.getByLabel('플랫폼',{exact:true}).selectOption('LeetCode');
    await expect(page.locator('.solution-row')).toHaveCount(23);
    await page.getByLabel('알고리즘',{exact:true}).selectOption('monotonic-deque');
    await expect(page.locator('.solution-row')).toHaveCount(1);
    await expect(page.locator('.solution-title')).toHaveText('Sliding Window Maximum');
    await page.getByLabel('문제 찾기').fill('Hard');
    await expect(page.locator('.solution-row')).toHaveCount(1);
    await page.getByLabel('문제 찾기').fill('unmatched');
    await expect(page.locator('.empty-state')).toBeVisible();
});

test('모바일 메뉴 포커스·Escape·문서 가독성', async ({page}) => {
    await page.setViewportSize({width:390,height:844});
    await page.goto('/');
    const menuBox = await page.getByRole('button',{name:'학습 메뉴 열기'}).boundingBox();
    expect(menuBox.x + menuBox.width).toBeLessThanOrEqual(390);
    await page.getByRole('button',{name:'학습 메뉴 열기'}).click();
    await expect(page.getByRole('dialog')).toBeVisible();
    await page.keyboard.press('Tab');
    expect(await page.evaluate(()=>document.querySelector('dialog').contains(document.activeElement))).toBe(true);
    await page.keyboard.press('Escape');
    await expect(page.getByRole('dialog')).not.toBeVisible();
    await expect(page.getByRole('button',{name:'학습 메뉴 열기'})).toBeFocused();
    await page.getByRole('button',{name:'학습 메뉴 열기'}).click();
    await page.locator('dialog a[href="/topics/sliding-window"]').click();
    await expect(page.locator('h1')).toHaveText('슬라이딩 윈도우');
    await expect(page.getByRole('dialog')).not.toBeVisible();
    await page.locator('.inline-toc summary').click();
    await page.locator('.inline-toc a[href="#steps"]').click();
    await expect(page).toHaveURL(/#steps$/);
    await expect(page.locator('#steps')).toBeInViewport();
    expect(await page.evaluate(()=>document.documentElement.scrollWidth<=innerWidth)).toBe(true);
    expect(await page.locator('pre').evaluate(el=>el.scrollHeight<=el.clientHeight+2)).toBe(true);
});

test('모바일 320px·태블릿·데스크톱과 잘못된 주소', async ({page}) => {
    for(const width of [320,768,1440]){
        await page.setViewportSize({width,height:900});
        for(const route of ['/','/topics/lca','/guide','/mistakes','/solutions']){
            await page.goto(route);
            expect(await page.evaluate(()=>document.documentElement.scrollWidth<=innerWidth),`${route} @${width}`).toBe(true);
        }
    }
    await page.goto('/topics/does-not-exist');
    await expect(page.locator('h1')).toHaveText('문서를 찾을 수 없습니다');
});

test('키보드 본문 건너뛰기', async ({page}) => {
    await page.goto('/');
    await page.keyboard.press('Tab');
    await expect(page.getByRole('link',{name:'본문으로 건너뛰기'})).toBeFocused();
    await page.keyboard.press('Enter');
    await expect(page.locator('main')).toBeFocused();
});
