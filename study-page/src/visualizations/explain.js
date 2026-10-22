const at = value => value < 0 ? '아직 정하지 않음' : String(value);
const counts = state => Object.entries(state.cnt || {}).map(([key, value]) => `${key}: ${value}`).join(', ') || '비어 있음';

export function stateRows(topic, state, input) {
    if (!state) return [['상태', '함수 실행 전']];
    if (topic === 'sliding-window') return [
        ['left', at(state.left)], ['right', state.right === input.s.length ? `${state.right} (순회 종료)` : at(state.right)],
        ['cnt', counts(state)], ['ans', String(state.ans)]
    ];
    if (topic === 'monotonic-deque') return [
        ['현재 인덱스 i', at(state.right)], ['구간 시작 i-K+1', state.right < 0 ? '아직 구간 없음' : String(state.left)],
        ['dq의 인덱스', `[${state.dq.join(', ')}]`], ['dq가 가리키는 값', `[${state.dq.map(i => input.nums[i]).join(', ')}]`],
        ['ans', `[${state.ans.join(', ')}]`]
    ];
    return [['left', at(state.left)], ['right', state.right === input.nums.length ? `${state.right} (end 경계)` : at(state.right)],
        ['mid', at(state.mid)], ['x', String(input.x)]];
}

export function explain(topic, step, input) {
    const a = step.after;
    const b = step.before;
    if (topic === 'sliding-window') {
        const now = input.s[a.right];
        const removed = a.current >= 0 ? String.fromCharCode(a.current) : '';
        const messages = {
            length: ['문자열 길이 저장', `len=${input.s.length}. 길이 200000 이하이므로 int로 저장. for의 종료 조건에 사용.`],
            reset: ['문자 빈도 초기화', 'fill(cnt,cnt+128,0)으로 전역 빈도 배열 초기화. 이전 호출의 빈도가 남으면 이번 문자열에 없는 문자까지 세게 됨.'],
            left: ['left를 0으로 초기화', '첫 문자부터 구간 시작. 중복 제거 때만 left를 늘리며 뒤로 되돌리지 않음.'],
            'answer-init': ['ans를 0으로 초기화', '아직 읽은 문자가 없으므로 길이 0. 빈 문자열이면 for를 건너뛰고 그대로 반환.'],
            visit: [`right=${a.right}로 이동`, `다음 문자는 s[${a.right}]='${now}'. 아직 cnt에 추가하지 않았으므로 이 단계에서는 길이를 기록하지 않음.`],
            character: [`오른쪽 문자 '${now}' 저장`, 'now=s[right]. 입력은 ASCII 0~127이므로 char 값을 cnt의 인덱스로 사용 가능.'],
            add: [`'${now}' 개수 ${b?.cnt[now] ?? 0} → ${a.cnt[now]}`, `cnt[now]++로 새 문자 추가. 추가한 뒤 검사해야 '${now}'의 중복을 발견 가능. 아직 중복이 있을 수 있으므로 답 갱신은 while 뒤.`],
            condition: [`cnt['${now}'] > 1 검사`, a.cnt[now] > 1
                ? `빈도 ${a.cnt[now]}이므로 중복. 왼쪽 문자를 하나 제거한 뒤 다시 검사. 한 번으로 중복이 없어지지 않을 수 있어 if 대신 while 필요.`
                : `빈도 ${a.cnt[now]}이므로 while 종료. 직전 구간에는 중복이 없었고 새 문자도 하나 이하이므로 전체 구간에 중복 없음.`],
            'remove-target': [`왼쪽 문자 '${removed}' 저장`, `next=s[left]=s[${a.left}]. 새 문자와 같은 문자만 골라 빼면 중간에 구멍이 생기므로 맨 왼쪽부터 순서대로 제거.`],
            remove: [`'${removed}' 개수 ${b?.cnt[removed]} → ${a.cnt[removed]}`, 'cnt[next]--로 현재 왼쪽 문자 제거. left부터 늘리면 다음 문자를 잘못 빼므로 빈도를 먼저 줄인 뒤 left 이동.'],
            'advance-left': [`left: ${b?.left} → ${a.left}`, `제거한 문자 다음 칸부터 새 구간 시작. 답을 바로 갱신하지 않고 중복 검사로 복귀. ${input.s === 'abba' && a.right === 2 && a.left === 1 ? "지금은 'bb'가 남아 한 번 더 제거." : '중복이 남으면 왼쪽 문자 제거를 계속.'}`],
            answer: [`길이 ${a.right - a.left + 1}로 최대 길이 갱신`, `[${a.left},${a.right}]는 양 끝 포함이므로 right-left+1. ans는 ${b?.ans} → ${a.ans}. 현재 구간이 짧아져도 이전 최장 길이를 보존하려고 max 사용.`],
            return: [`최장 길이 ${a.ans} 반환`, '마지막 문자까지 확인 완료. 중복을 모두 제거한 뒤 길이를 비교했으므로 ans는 중복 없는 최장 구간의 길이.']
        };
        return messages[step.event];
    }
    if (topic === 'monotonic-deque') {
        const i = a.right;
        const front = a.dq?.[0];
        const back = a.dq?.at(-1);
        const messages = {
            length: ['배열 길이 저장', `len=${input.nums.length}. K의 범위와 i<len 검사에 사용.`],
            reset: ['이전 정답 제거', 'ans.clear()로 전역 결과 초기화. 이전 호출에서 구한 구간 최댓값이 섞이지 않도록 매번 비우기.'],
            validity: ['K 범위 검사', input.K <= 0 || input.K > input.nums.length ? `K=${input.K}, 배열 길이=${input.nums.length}. 길이 K 구간을 만들 수 없으므로 빈 결과 반환.` : '1<=K<=N이므로 진행. 범위 검사 후 후보 덱 생성.'],
            'deque-init': ['빈 인덱스 덱 생성', '값 대신 인덱스 저장. 같은 값도 들어온 위치가 다르면 구간에서 빠지는 순서가 다르므로 위치 필요.'],
            visit: [`i=${i}, 새 값 ${input.nums[i]}`, `현재 구간 시작은 i-K+1=${a.left}. ${a.left < 0 ? '시작점이 음수이므로 아직 K개 미만. 후보만 정리.' : '이 시작점보다 작은 인덱스는 현재 구간 밖.'}`],
            'expire-check': ['덱 앞의 만료 검사', front === undefined ? '덱이 비었으므로 front 접근 생략. && 왼쪽에서 empty를 먼저 검사해야 범위 밖 접근 방지.' : `앞 인덱스 ${front}, 구간 시작 ${a.left}. ${front < a.left ? '구간 시작보다 작으므로 앞에서 제거.' : '아직 구간 안이므로 앞 제거 종료.'}`],
            expire: [`앞 인덱스 ${b?.dq?.[0]} 제거`, `현재 구간 밖이므로 값이 커도 최댓값 후보에서 제외. dq=[${a.dq.join(', ')}]. 다음 앞 인덱스도 만료됐는지 재검사.`],
            'back-check': ['덱 뒤와 새 값 비교', back === undefined ? '덱이 비었으므로 비교 종료. 현재 인덱스 추가 가능.' : `뒤 값 ${input.nums[back]}, 새 값 ${input.nums[i]}. ${input.nums[back] <= input.nums[i] ? '뒤 값이 작거나 같고 더 먼저 만료되므로 제거 가능.' : '뒤 값이 더 크므로 둘 다 후보로 유지.'}`],
            'drop-back': [`뒤 인덱스 ${b?.dq?.at(-1)} 제거`, '새 값이 더 크거나 같고 더 늦게 만료. 기존 뒤 후보가 다시 최댓값이 될 수 없으므로 제거. 앞에서는 만료, 뒤에서는 값과 만료 순서를 비교.'],
            push: [`인덱스 ${i}를 뒤에 추가`, `dq=[${a.dq.join(', ')}], 값=[${a.dq.map(j => input.nums[j]).join(', ')}]. 인덱스는 증가, 값은 감소하는 순서 유지.`],
            'window-check': ['K개 완성 여부 검사', i >= input.K - 1 ? `${i}>=${input.K - 1}이므로 K개 이상 처리 완료. 덱 앞의 값을 정답에 추가.` : `${i}<${input.K - 1}이므로 아직 K개 미만. 답 추가 생략.`],
            answer: [`최댓값 ${input.nums[front]} 추가`, `만료되지 않은 후보 중 가장 큰 값이 덱 앞. ans=[${(b?.ans || []).join(', ')}] → [${a.ans.join(', ')}].`],
            return: [`결과 [${a.ans.join(', ')}] 반환`, '완성된 구간마다 최댓값 하나씩 기록. 각 인덱스는 한 번 추가·최대 한 번 제거하므로 전체 O(N).']
        };
        return messages[step.event];
    }
    const mid = a.mid >= 0 ? a.mid : b?.mid;
    const messages = {
        length: ['배열 길이 저장', `len=${input.nums.length}. 인덱스와 제외 끝은 0~len이므로 int로 충분.`],
        left: ['left를 0으로 초기화', '아직 x 미만으로 확인한 원소가 없으므로 첫 위치부터 후보에 포함.'],
        right: [`right를 N=${input.nums.length}으로 초기화`, '미확정 구간은 [left,right). right는 제외 끝이므로 N까지 허용. nums[N]은 읽지 않음.'],
        condition: [`left < right 검사: ${a.left} < ${a.right}`, a.left < a.right ? '미확정 원소가 남았으므로 mid 계산.' : '미확정 구간이 비어 반복 종료. 두 경계가 만난 위치가 x 이상인 첫 위치. 없으면 N 반환.'],
        middle: [`mid=${mid} 계산`, `left+(right-left)/2로 중간 인덱스 계산. 정수 나눗셈으로 내림. [${a.left},${a.right}) 안의 nums[${mid}]=${input.nums[mid]} 비교.`],
        compare: [`nums[${mid}]=${input.nums[mid]} < x=${input.x} 검사`, input.nums[mid] < input.x ? '중간값이 x 미만. 정렬돼 있으므로 mid 왼쪽도 모두 x 미만. mid까지 제외하려고 left=mid+1 사용.' : '중간값이 x 이상. mid가 첫 위치일 수 있으므로 right=mid로 경계에 남기기.'],
        'move-left': [`left: ${b?.left} → ${a.left}`, `nums[mid]<x이므로 mid까지 제외. 남은 구간은 [${a.left},${a.right}). left=mid로 두면 원소 하나가 남았을 때 경계가 움직이지 않아 무한 반복 가능.`],
        'move-right': [`right: ${b?.right} → ${a.right}`, 'mid가 x 이상이므로 그 오른쪽은 첫 위치가 될 수 없음. right=mid로 줄여 답 경계 보존. right=mid-1은 닫힌 구간 규칙이므로 혼용 금지.'],
        return: [`첫 위치 ${a.left} 반환`, a.left === input.nums.length ? '모든 값이 x 미만이므로 end 인덱스 N 반환. nums[N]은 범위 밖. 반환 위치의 값을 읽기 전에 인덱스<N 검사.' : `nums[${a.left}]=${input.nums[a.left]}가 x 이상인 첫 값. 앞의 값은 모두 x 미만이라는 불변식 유지.`]
    };
    return messages[step.event];
}
