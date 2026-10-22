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
            length: ['길이를 int len에 저장한다', `입력 길이는 ${input.s.length}입니다. 길이 200000 이하를 전제로 int로 저장한 뒤 반복문의 경계로 사용합니다.`],
            reset: ['빈도 배열을 0으로 만든다', '전역 cnt는 이전 실행의 값이 남을 수 있습니다. fill(cnt, cnt + 128, 0)으로 고정 빈도 배열을 모두 비웁니다. 아직 구간은 만들지 않았습니다.'],
            left: ['구간의 시작을 0으로 둔다', '첫 문자를 읽기 전이므로 왼쪽 시작점은 0입니다. left는 중복을 제거할 때만 앞으로 이동하며 뒤로 돌아가지 않습니다.'],
            'answer-init': ['정답을 0으로 시작한다', '아직 유효한 문자를 한 개도 처리하지 않았습니다. 빈 문자열이 입력되면 반복문 없이 이 0을 반환합니다.'],
            visit: [`right를 ${a.right}번으로 이동한다`, `이제 s[${a.right}]인 '${now}'를 읽을 차례입니다. 오른쪽 끝만 늘렸을 뿐 빈도에는 아직 반영하지 않았으므로, 이 시점의 구간으로 답을 갱신하지 않습니다.`],
            character: [`현재 문자 '${now}'를 읽는다`, 'now에는 새로 포함할 문자 하나를 저장합니다. 이 예제의 입력은 ASCII 0~127이라 char 값이 그대로 빈도 배열의 유효 인덱스입니다.'],
            add: [`'${now}'의 빈도를 ${b?.cnt[now] ?? 0} → ${a.cnt[now]}로 늘린다`, `새 오른쪽 원소를 먼저 반영해야 '${now}'가 중복됐는지 검사할 수 있습니다. 여기서는 아직 구간이 잘못되었을 수 있으므로 길이를 정답에 넣지 않습니다.`],
            condition: [`중복 조건 cnt['${now}'] > 1을 검사한다`, a.cnt[now] > 1
                ? `현재 빈도는 ${a.cnt[now]}이므로 조건이 참입니다. 왼쪽 원소를 하나 제거하러 들어갑니다. 한 번 제거한 뒤에도 중복일 수 있어 if가 아닌 while입니다.`
                : `현재 빈도는 ${a.cnt[now]}이므로 조건이 거짓입니다. 이전 구간에는 중복이 없었고 새 문자도 하나 이하가 되었으므로, 이제 전체 구간이 유효합니다.`],
            'remove-target': [`왼쪽에서 뺄 문자 '${removed}'를 읽는다`, `s[left]인 s[${a.left}]를 next에 보관합니다. 새 문자와 같은 문자만 지우는 것이 아니라, 구간의 맨 왼쪽부터 차례로 빼야 연속 구간을 유지합니다.`],
            remove: [`'${removed}'의 빈도를 ${b?.cnt[removed]} → ${a.cnt[removed]}로 줄인다`, '현재 left 위치의 문자를 빈도에서 먼저 뺍니다. left를 먼저 늘리면 원래 왼쪽 문자가 아닌 다음 문자를 지워 배열과 구간의 의미가 어긋납니다. 다음 줄에서 left도 옮겨 두 상태를 맞춥니다.'],
            'advance-left': [`left를 ${b?.left} → ${a.left}로 옮긴다`, `빠진 문자의 다음 위치를 구간 시작으로 삼습니다. 바로 답을 갱신하지 않고 while 조건으로 돌아갑니다. ${input.s === 'abba' && a.right === 2 && a.left === 1 ? "지금은 'bb'가 남아 있으므로 한 번 더 제거해야 합니다." : '중복이 남아 있으면 제거를 계속합니다.'}`],
            answer: [`유효한 길이 ${a.right - a.left + 1}로 ans를 갱신한다`, `[${a.left}, ${a.right}]는 양 끝을 포함하므로 길이가 right-left+1입니다. ans는 ${b?.ans} → ${a.ans}입니다. 짧은 유효 구간이 나와도 이전 최장 길이를 잃지 않도록 max를 씁니다.`],
            return: [`최장 길이 ${a.ans}을 반환한다`, '오른쪽 끝을 마지막 문자까지 모두 확인했습니다. 각 단계에서 조건을 복구한 뒤 길이를 비교했으므로 ans에는 전체 입력의 최장 길이가 남습니다.']
        };
        return messages[step.event];
    }
    if (topic === 'monotonic-deque') {
        const i = a.right;
        const front = a.dq?.[0];
        const back = a.dq?.at(-1);
        const messages = {
            length: ['원소 수를 int len에 저장한다', `원소 수는 ${input.nums.length}입니다. 이후 K의 유효 범위와 i<len을 이 길이로 검사합니다.`],
            reset: ['이전 정답을 비운다', 'ans는 전역 배열입니다. 실행마다 clear해서 이전 윈도우의 결과가 섞이지 않게 합니다.'],
            validity: ['윈도우 길이를 검사한다', input.K <= 0 || input.K > input.nums.length ? `K=${input.K}로는 길이 ${input.nums.length}의 배열에서 유효한 구간을 만들 수 없습니다. 빈 결과로 바로 돌아갑니다.` : `1≤K≤N을 만족합니다. 이제 후보 덱을 만들어 순회합니다.`],
            'deque-init': ['인덱스를 담을 빈 덱을 만든다', '덱에는 값이 아닌 인덱스를 저장합니다. 같은 값도 들어온 시각과 만료 시점이 다르기 때문입니다.'],
            visit: [`i=${i}, 새 값 ${input.nums[i]}을 처리한다`, `구간의 닫힌 시작은 i-K+1=${a.left}입니다. ${a.left < 0 ? '아직 K개가 모이지 않아 완성된 윈도우가 아닙니다.' : '이 시작점보다 작은 인덱스는 만료됩니다.'}`],
            'expire-check': ['앞쪽 후보의 만료를 검사한다', front === undefined ? '덱이 비어 있어 front에 접근하지 않습니다. empty 검사가 &&의 왼쪽에 있어 안전합니다.' : `앞 인덱스 ${front}가 구간 시작 ${a.left}보다 ${front < a.left ? '작으므로 제거합니다.' : '작지 않아 아직 유효합니다. 만료 제거를 끝냅니다.'}`],
            expire: [`만료된 인덱스 ${b?.dq?.[0]}을 앞에서 뺀다`, `이 원소는 현재 구간에 없으므로 값이 아무리 커도 답이 될 수 없습니다. dq는 [${a.dq.join(', ')}]가 됩니다. 만료 검사를 다시 합니다.`],
            'back-check': ['뒤쪽 후보가 새 값에 밀리는지 검사한다', back === undefined ? '덱이 비어 있어 비교할 후보가 없습니다. 현재 인덱스를 넣을 수 있습니다.' : `기존 뒤 값 ${input.nums[back]}과 새 값 ${input.nums[i]}을 비교합니다. ${input.nums[back] <= input.nums[i] ? '기존 값이 작거나 같고 더 일찍 만료되므로 영구히 버릴 수 있습니다.' : '기존 값이 더 크므로 둘 다 후보로 남깁니다.'}`],
            'drop-back': [`뒤의 인덱스 ${b?.dq?.at(-1)}을 제거한다`, '새 원소가 값은 더 크거나 같고 더 늦게 만료됩니다. 이전 후보가 앞으로 최댓값이 될 가능성이 없어 뒤에서 제거합니다. 앞의 만료 제거와 이유가 다릅니다.'],
            push: [`현재 인덱스 ${i}를 뒤에 넣는다`, `dq=[${a.dq.join(', ')}], 해당 값=[${a.dq.map(j => input.nums[j]).join(', ')}]입니다. 인덱스는 증가하고 값은 감소하는 순서가 유지됩니다.`],
            'window-check': ['윈도우가 완성됐는지 검사한다', i >= input.K - 1 ? `${i}≥${input.K - 1}이므로 K개가 모였습니다. front가 가리키는 값을 정답에 추가합니다.` : `${i}<${input.K - 1}이므로 아직 K개가 없습니다. 이 상태에서는 답을 추가하지 않습니다.`],
            answer: [`front의 값 ${input.nums[front]}을 정답에 추가한다`, `유효한 후보 중 가장 큰 값이 앞에 있습니다. ans는 [${(b?.ans || []).join(', ')}] → [${a.ans.join(', ')}]가 됩니다.`],
            return: [`전체 결과 [${a.ans.join(', ')}]로 종료한다`, '각 완성된 윈도우마다 한 번씩 답을 추가했습니다. 각 인덱스는 한 번 들어가고 최대 한 번 제거되므로 전체 시간이 O(N)입니다.']
        };
        return messages[step.event];
    }
    const mid = a.mid >= 0 ? a.mid : b?.mid;
    const messages = {
        length: ['길이를 int len에 저장한다', `배열 길이 ${input.nums.length}을 먼저 저장합니다. 인덱스와 제외 끝은 0~len이므로 int로 표현합니다.`],
        left: ['left를 0으로 둔다', '아직 어떤 값도 x 미만이라고 제외하지 않았습니다. 가장 왼쪽 원소부터 정답 후보에 포함합니다.'],
        right: [`right를 N=${input.nums.length}으로 둔다`, '탐색 구간은 [left,right)입니다. right는 제외 끝이므로 N이 될 수 있습니다. arr[N]에 접근한다는 뜻이 아닙니다.'],
        condition: [`left < right를 검사한다: ${a.left} < ${a.right}`, a.left < a.right ? '미확정 원소가 남아 있어 중간을 비교합니다.' : '미확정 구간이 비었습니다. 두 경계가 만난 위치가 x 이상인 최초 위치이며, 없으면 N입니다.'],
        middle: [`mid=${mid}를 계산한다`, `left+(right-left)/2에서 정수 나눗셈을 합니다. 현재 [${a.left},${a.right})의 중간 원소 arr[${mid}]=${input.nums[mid]}을 비교합니다.`],
        compare: [`arr[${mid}]=${input.nums[mid]} < x=${input.x}를 비교한다`, input.nums[mid] < input.x ? '중간값이 x보다 작습니다. 정렬되어 있으므로 mid 이전도 모두 x 미만입니다. mid까지 제외하려면 left=mid+1이어야 합니다.' : '중간값이 x 이상입니다. mid가 첫 위치일 수도 있으므로 버리면 안 됩니다. right=mid로 두어 답 경계로 남깁니다.'],
        'move-left': [`left: ${b?.left} → ${a.left}`, `arr[mid]가 x보다 작았으므로 mid까지 버립니다. [${a.left},${a.right})만 남습니다. left=mid로 두면 원소가 한 개일 때 구간이 줄지 않을 수 있습니다.`],
        'move-right': [`right: ${b?.right} → ${a.right}`, `mid가 x 이상이므로 그보다 오른쪽은 첫 위치가 될 수 없습니다. right=mid로 줄여 mid라는 경계를 유지합니다. right=mid-1로 줄이는 닫힌 구간 방식과 혼용하지 않습니다.`],
        return: [`첫 위치 ${a.left}을 반환한다`, a.left === input.nums.length ? '모든 값이 x보다 작아 반환값은 end 인덱스 N입니다. 이 위치의 배열 값을 읽으면 범위 밖이므로, 값을 사용할 때는 먼저 인덱스<N을 확인해야 합니다.' : `arr[${a.left}]=${input.nums[a.left]}가 x 이상인 첫 값입니다. 앞의 값들은 모두 x 미만이라는 불변식이 유지되었습니다.`]
    };
    return messages[step.event];
}
