import { test, expect } from '@playwright/test';
import fs from 'node:fs/promises';
import sliding from '../src/data/traces/sliding-window.json' with { type: 'json' };
import deque from '../src/data/traces/monotonic-deque.json' with { type: 'json' };
import binary from '../src/data/traces/binary-search.json' with { type: 'json' };

for (const data of [sliding, deque, binary]) {
    test(`${data.topic}: 모든 입력·실행 단계·줄 번호·경계·초기화`, async ({page}) => {
        test.setTimeout(120000);
        const errors=[];page.on('pageerror',error=>errors.push(error.message));
        const code=await fs.readFile(new URL(`../templates/${data.topic}.cpp`,import.meta.url),'utf8');
        await page.goto(`/topics/${data.topic}#trace`);
        const visual=page.locator('.step-visualizer');
        const next=visual.getByRole('button',{name:'다음 →',exact:true});
        const previous=visual.getByRole('button',{name:'← 이전',exact:true});
        const reset=visual.getByRole('button',{name:'초기화',exact:true});
        for (const [caseIndex,example] of data.cases.entries()) {
            await page.getByLabel('시각화 입력',{exact:true}).selectOption(String(caseIndex));
            await expect(previous).toBeDisabled();await expect(reset).toBeDisabled();
            for (const [index,step] of example.steps.entries()) {
                await expect(visual).toHaveAttribute('data-event',step.event);
                await expect(visual).toHaveAttribute('data-step',String(index));
                await expect(visual.locator('[data-active-line]')).toHaveAttribute('data-active-line',String(step.line));
                const start=Math.max(1,step.line-2),end=Math.min(code.trimEnd().split('\n').length,step.line+2);
                expect(await visual.locator('pre code').textContent()).toBe(code.trimEnd().split('\n').slice(start-1,end).join('\n'));
                await expect(visual.locator('.step-reason')).not.toContainText(/undefined|NaN|(?<!아)니다|세요|원소 반영|조건 복구|해당 시점/);
                const marker=await visual.locator('.execution-marker').boundingBox();
                const body=await visual.locator('.code-body').boundingBox();
                expect(Math.abs(marker.y-body.y-(20+(step.line-start)*28))).toBeLessThan(1);
                if(index+1<example.steps.length)await next.click();
            }
            await expect(next).toBeDisabled();
            if(data.topic==='sliding-window')await expect(visual.locator('tbody tr').last().locator('td').last()).toHaveText(String(example.expected));
            if(data.topic==='monotonic-deque')await expect(visual.locator('tbody tr').last().locator('td').last()).toHaveText(`[${example.expected.join(', ')}]`);
            if(data.topic==='binary-search')await expect(visual.locator('tbody tr').first().locator('td').last()).toHaveText(String(example.expected));
            await previous.click();await expect(visual).toHaveAttribute('data-step',String(example.steps.length-2));
            if(example.steps.length>2)await reset.click();
            else await expect(reset).toBeDisabled();
            await expect(visual).toHaveAttribute('data-step','0');
        }
        expect(errors).toEqual([]);
    });
}

test('abba: if 한 번으로 복구되지 않는 순간과 복구 후 답 갱신', async ({page}) => {
    await page.goto('/topics/sliding-window#trace');
    const target=sliding.cases[0].steps.findIndex(s=>s.event==='advance-left'&&s.after.right===2&&s.after.left===1);
    const visual=page.locator('.step-visualizer');
    for(let i=0;i<target;i++)await visual.getByRole('button',{name:'다음 →',exact:true}).click();
    await expect(visual.locator('.step-reason')).toContainText("'bb'가 남아");
    await expect(visual.locator('tbody')).toContainText('b: 2');
    await expect(visual.locator('tbody tr').last().locator('td').last()).toHaveText('2');
});

test('흰 본문·18px 설명·16px 코드와 표·전체 코드 펼침', async ({page}) => {
    for(const width of [320,390,768,1440]){
        await page.setViewportSize({width,height:1000});
        for(const id of ['sliding-window','monotonic-deque','binary-search','segment-tree','lca']){
            await page.goto(`/topics/${id}`);
            expect(await page.evaluate(()=>document.documentElement.scrollWidth<=innerWidth),`${id} @${width}`).toBe(true);
            expect(await page.locator('#conditions p').first().evaluate(el=>getComputedStyle(el).fontSize)).toBe('18px');
            expect(await page.locator('#template pre').evaluate(el=>getComputedStyle(el).fontSize)).toBe('16px');
            expect(await page.locator('#variables table').evaluate(el=>getComputedStyle(el).fontSize)).toBe('16px');
            const blocks=await page.locator('pre').evaluateAll(els=>els.map(el=>({height:el.scrollHeight,visible:el.clientHeight})));
            expect(blocks.every(b=>b.height<=b.visible+2)).toBe(true);
            const backgrounds=await page.locator('article section, article h2, article p, table, th, td').evaluateAll(els=>els.map(el=>getComputedStyle(el).backgroundColor));
            expect(backgrounds.every(color=>['rgba(0, 0, 0, 0)','rgb(255, 255, 255)'].includes(color))).toBe(true);
            const tokens=await page.locator('#template .token.keyword').filter({hasText: /^using$/}).first().evaluate(el=>getComputedStyle(el).color);
            expect(tokens).toBe('rgb(0, 0, 189)');
        }
    }
});

test('단계 버튼 키보드 조작과 모바일 줄 강조',async({page})=>{
    await page.setViewportSize({width:390,height:844});
    await page.goto('/topics/sliding-window#trace');
    const visual=page.locator('.step-visualizer');
    await visual.getByRole('button',{name:'다음 →',exact:true}).focus();await page.keyboard.press('Enter');
    await expect(visual).toHaveAttribute('data-step','1');
    await visual.getByRole('button',{name:'← 이전',exact:true}).focus();await page.keyboard.press('Space');
    await expect(visual).toHaveAttribute('data-step','0');
    expect(await page.locator('html').evaluate(el=>el.scrollWidth<=innerWidth)).toBe(true);
});

test('설명 속 C++ 간격·단항 연산·템플릿·시각화 입력·수식 검색', async ({page}) => {
    await page.goto('/topics/euler-tour');
    await expect(page.locator('#conditions')).toContainText('1 <= N <= 200000');
    await expect(page.locator('#steps')).toContainText('tin[now] = timer, order[timer] = now');
    await expect(page.locator('#trace')).toContainText('tin[0] = 0, timer = 1');
    await page.goto('/topics/bits');
    await expect(page.locator('#steps')).toContainText('mask &= ~(1 << idx)');
    await expect(page.locator('#steps')).toContainText('(mask & (1 << idx)) != 0');
    await page.goto('/topics/heap');
    await expect(page.locator('#steps')).toContainText('priority_queue<int, vector<int>, greater<int>>');
    await page.goto('/topics/monotonic-deque#trace');
    await expect(page.locator('.example-input')).toContainText('nums = [4, 2, 3, 1], K = 2');
    await expect(page.getByLabel('시각화 입력').locator('option').first()).toHaveText('앞 만료와 뒤 제거: [4, 2, 3, 1], K = 2');
    await expect(page.locator('.step-visualizer tbody')).toContainText('구간 시작 i - K + 1');
    for (const query of ['tin[now]=timer', 'tin[now] = timer']) {
        await page.goto(`/search?q=${encodeURIComponent(query)}`);
        await expect(page.locator('.search-results a[href="/topics/euler-tour"]')).toBeVisible();
    }
});
