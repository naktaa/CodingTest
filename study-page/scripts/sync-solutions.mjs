import { readdir, readFile, writeFile } from 'node:fs/promises';
import { existsSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import path from 'node:path';
import { execFileSync } from 'node:child_process';
import { createHash } from 'node:crypto';

const project = fileURLToPath(new URL('../', import.meta.url));
const repo = path.resolve(project, '..');
const metadata = JSON.parse(await readFile(path.join(project, 'data/problems.json'), 'utf8'));
const catalog = JSON.parse(await readFile(path.join(project, 'src/content/catalog.json'), 'utf8'));
const validTopics = new Set(catalog.map(x => x.id));
const folders = {
    'DP': ['dp'], 'MST': ['mst', 'dsu'], 'Union-find': ['dsu'],
    'Greedy': ['greedy'], '해시': ['frequency'], '해시맵': ['frequency'],
    '문자열': ['implementation'], '정렬': ['sorting'],
    '구현+시뮬레이션': ['implementation'], '그래프': ['dfs', 'bfs'],
    'DFS+BFS': ['dfs', 'bfs'], '최단거리': ['dijkstra'],
    '트리': ['tree'], '누적합': ['prefix'], '투포인터': ['two-pointers'],
    '매개변수탐색': ['parametric'], '이분탐색': ['binary-search'],
    '백트래킹': ['backtracking', 'permutations'], '비트마스킹': ['bits'],
    '수학': ['math'], '완전탐색': ['bruteforce'], '우선순위큐': ['heap'],
    '자료구조': ['stack-queue'], '스택+큐': ['stack-queue'], '힙': ['heap'],
    '단조스택+큐': ['monotonic-stack'], '슬라이딩윈도우': ['sliding-window'],
    '위상정렬': ['topological'], '재귀_분할정복': ['dfs', 'bruteforce']
};
const overrides = {
    'LeetCode:1094': ['difference'], 'LeetCode:1109': ['difference'],
    'LeetCode:239': ['monotonic-deque', 'sliding-window'],
    'LeetCode:739': ['monotonic-stack'], 'LeetCode:84': ['monotonic-stack'],
    'LeetCode:209': ['sliding-window', 'two-pointers'],
    'LeetCode:56': ['intervals', 'sorting'], 'LeetCode:347': ['frequency', 'heap'],
    'LeetCode:1494': ['bitmask-dp', 'topological'], 'LeetCode:1879': ['bitmask-dp'],
    'LeetCode:1986': ['bitmask-dp'], 'LeetCode:698': ['backtracking', 'bitmask-dp'],
    'LeetCode:1235': ['dp', 'binary-search'], 'LeetCode:787': ['bellman-ford', 'dp'],
    'Baekjoon:2098': ['bitmask-dp'], 'Baekjoon:1029': ['bitmask-dp'],
    'Baekjoon:11066': ['interval-dp'], 'Baekjoon:12865': ['knapsack'],
    'Baekjoon:1106': ['knapsack'], 'Baekjoon:22963': ['lis'],
    'Baekjoon:2533': ['tree-dp'], 'Baekjoon:15681': ['tree', 'tree-dp', 'euler-tour'],
    'Baekjoon:3584': ['lca', 'tree'], 'Baekjoon:1991': ['tree'],
    'Baekjoon:11404': ['floyd'], 'Baekjoon:11780': ['floyd'],
    'Baekjoon:14938': ['floyd'], 'Baekjoon:1956': ['floyd'],
    'Baekjoon:1261': ['zero-one-bfs'], 'Baekjoon:13549': ['zero-one-bfs'],
    'Baekjoon:2665': ['zero-one-bfs'], 'Baekjoon:17835': ['dijkstra'],
    'Baekjoon:7576': ['multi-bfs'], 'Baekjoon:4179': ['multi-bfs', 'bfs'],
    'Baekjoon:2206': ['state-bfs'], 'Baekjoon:1525': ['state-bfs'],
    'Baekjoon:6087': ['state-bfs', 'zero-one-bfs'],
    'Baekjoon:16946': ['dfs', 'dsu'], 'Baekjoon:2170': ['intervals'],
    'Baekjoon:1806': ['sliding-window', 'prefix'], 'Baekjoon:13904': ['heap-simulation', 'greedy'],
    'Baekjoon:14891': ['implementation'], 'Baekjoon:1992': ['dfs'],
    'Baekjoon:2141': ['greedy', 'sorting'], 'Baekjoon:1028': ['dp'],
    'JUNGOL:1077': ['knapsack'], 'JUNGOL:2616': ['knapsack'],
    'JUNGOL:1681': ['backtracking'], 'JUNGOL:1027': ['backtracking'],
    'JUNGOL:1840': ['bfs', 'implementation'], 'JUNGOL:1848': ['dp'],
    'JUNGOL:2553': ['sorting', 'greedy'], 'JUNGOL:3078': ['state-bfs']
};
const titleOverrides = {
    '순위': ['floyd'], '입국심사': ['parametric', 'binary-search'],
    '섬 연결하기': ['mst', 'dsu'], '타겟 넘버': ['dfs', 'bruteforce'],
    '퍼즐 조각 채우기': ['bfs', 'implementation'], '기능개발': ['stack-queue', 'implementation'],
    '전력망을 둘로 나누기': ['tree', 'bruteforce'], '도둑질': ['dp'],
    '구명보트': ['greedy', 'two-pointers'], '단속카메라': ['greedy', 'intervals'],
    '가장 큰 수': ['sorting'], '더맵게': ['heap', 'heap-simulation']
};
const repository = JSON.parse(await readFile(path.join(project, 'data/repository.json'), 'utf8'));
let commit = repository.commit;
let tracked = new Set(repository.trackedPaths);
try {
    const currentCommit = execFileSync('git', ['rev-parse', 'HEAD'], { cwd: repo, encoding: 'utf8', stdio: ['ignore', 'pipe', 'pipe'] }).trim();
    const currentPaths = execFileSync('git', ['ls-files', '-z'], { cwd: repo, encoding: 'utf8', stdio: ['ignore', 'pipe', 'pipe'] }).split('\0');
    commit = currentCommit;
    tracked = new Set(currentPaths);
} catch {
    console.warn('Git 조회 불가: 확인해 둔 커밋의 풀이 링크를 사용합니다.');
}
async function walk(dir) {
    const entries = await readdir(dir, { withFileTypes: true });
    const nested = await Promise.all(entries.map(async entry => {
        const name = path.join(dir, entry.name);
        return entry.isDirectory() ? walk(name) : [name];
    }));
    return nested.flat();
}
const solutions = [];
for (const platform of ['Baekjoon', 'LeetCode', 'Programmers', 'JUNGOL']) {
    const dir = path.join(repo, platform);
    if (!existsSync(dir)) continue;
    for (const file of await walk(dir)) {
        if (!file.endsWith('.cpp') || path.basename(file).startsWith('tempCodeRunner')) continue;
        const relative = path.relative(repo, file).split(path.sep).join('/');
        if (relative.startsWith('Baekjoon/6086_')) continue;
        const stem = path.basename(file, '.cpp');
        const meta = metadata[relative] ?? {};
        const id = meta.id ?? stem.split('_')[0];
        const title = meta.title ?? stem.replace(/^\d+_/, '').replaceAll('+', ' ');
        let topicIds = titleOverrides[title] ?? overrides[`${platform}:${id}`] ?? folders[relative.split('/')[1]] ?? ['implementation'];
        topicIds = topicIds.filter(x => validTopics.has(x));
        const code = await readFile(file, 'utf8');
        solutions.push({
            ...meta, id, title, platform, path: relative, topics: topicIds, code,
            codeHash: createHash('sha256').update(code).digest('hex'),
            githubUrl: tracked.has(relative) ? `https://github.com/naktaa/CodingTest/blob/${commit}/${relative.split('/').map(encodeURIComponent).join('/')}` : null,
            localOnly: !tracked.has(relative)
        });
    }
}
solutions.sort((a, b) => a.platform.localeCompare(b.platform) || a.title.localeCompare(b.title, 'ko'));
await writeFile(path.join(project, 'src/data/solutions.json'), JSON.stringify(solutions, null, 2) + '\n');
console.log(`내 풀이 ${solutions.length}개 연결 · 난이도 확인 ${solutions.filter(x => x.difficulty).length}개`);
