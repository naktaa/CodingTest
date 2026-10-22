# 알고리즘 공부 노트

`CodingTest`의 C++ 풀이와 연결한 개인용 공부 페이지입니다. 기본·핵심·확장 알고리즘 45개, 처리 순서와 경계 실수 노트, 선택 가이드, 시험 직전 요약을 정리했습니다. 흰 바탕의 문서 화면에서 전체 템플릿과 실행 순서를 읽고, 슬라이딩 윈도우·단조 덱·이분탐색은 한 단계씩 따라갈 수 있습니다. 검색·유형별 탐색·코드 복사를 지원합니다.

Windows에서 Node.js 22.12 이상을 사용합니다. `E:\CodingTest\study-page\start.cmd`를 더블클릭하면 필요한 의존성을 준비하고 서버와 브라우저를 실행합니다. 사용하는 동안 실행 창을 열어 두세요. 창을 닫으면 서버도 종료됩니다.

VS Code의 PowerShell 터미널에서는 처음 한 번 설치합니다. `npm.ps1` 실행 정책 오류를 피하도록 `npm.cmd`를 사용합니다.

```powershell
cd E:\CodingTest\study-page
npm.cmd install
npm.cmd run dev
```

다음 실행부터는 `start.cmd`를 더블클릭하거나 `npm.cmd run dev`만 실행하면 됩니다. 서버가 켜져 있는 동안 페이지 이동·새로고침에는 명령을 다시 입력하지 않아도 됩니다.

브라우저에서 `http://localhost:5173`을 엽니다. 다른 포트가 표시되면 터미널에 나온 주소를 사용하세요. `npm.cmd run build`로 빌드하고 `npm.cmd run preview`로 빌드 결과를 확인합니다. PowerShell 실행 정책은 변경하지 않습니다.

- `src/content/topics/` — 주제별 문서
- `AGENTS.md` — 기존 풀이 5개를 기준으로 기록한 C++ 작성 규칙
- `templates/` — 화면에서 그대로 표시하는 기본 C++17 함수
- `src/data/traces/` — 실제 C++ 실행에서 생성한 단계별 시각화 기록
- `data/problems.json` — 출처와 확인 날짜가 있는 문제 정보
- `scripts/sync-solutions.mjs` — 기존 풀이를 읽어 목록 갱신 (`npm run sync`; 실행·빌드 때도 자동 갱신)

기존 풀이를 바꾼 뒤 서버를 다시 실행하거나 `npm run sync`를 실행하면 반영됩니다. 난이도는 원문 또는 명시한 기록 기준이며 미확인 값은 추정하지 않습니다. [정보 출처](docs/THIRD_PARTY_NOTICES.md) · [검증 기록](docs/VALIDATION.md)
