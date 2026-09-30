# 과제 1: Compare sorting

삽입 정렬, 병합 정렬, 힙 정렬을 C17로 구현한 비교 실험입니다.

- 작성 대상: 김무선 / 2026193106
- 보고서: `report/sorting_report.pdf` (6쪽)
- 편집 가능한 보고서: `report/REPORT.md`
- 실제 실험 원본: `report/results.csv`
- 세 정렬 모두 `Record { key, original }`의 key만 비교합니다.
- 시간 측정과 연산 횟수 측정은 별도로 실행합니다.

## 실행

GitHub Codespaces 또는 GCC와 make가 있는 Linux 환경에서 저장소 루트의 터미널에 입력합니다.

```sh
make test
make run
```

`make test`의 기대 출력은 `624 checks, 0 failures`입니다.
`make run`은 60개 조건별 결과 행을 CSV로 출력합니다.

```sh
make bench
```

위 명령은 `report/results.csv`를 현재 환경의 측정값으로 교체합니다. 실행 시간은 환경에 따라 달라집니다. 제공된 PDF는 패키지에 포함된 최초 CSV의 결과입니다. CSV를 교체하면 보고서도 다시 만들어야 합니다.

## PDF와 그래프 다시 만들기

보고서 생성 도구만 reportlab, matplotlib가 필요합니다. 정렬 실험 코드는 외부 라이브러리를 사용하지 않습니다.

```sh
python3 -m pip install reportlab matplotlib
python3 tools/make_report.py --repo-url https://github.com/본인아이디/저장소이름
```

실제 영문 GitHub 아이디와 저장소 이름으로 URL을 바꾸세요. PDF, Markdown과 그래프가 현재 CSV를 이용하여 생성됩니다. URL을 지정하지 않으면 PDF 마지막 페이지에 입력 가능한 빈 URL 필드가 만들어집니다. PDF 편집기나 브라우저에서 해당 칸을 채우고 저장할 수도 있습니다.

다른 운영체제나 컴파일러에서 실험을 다시 수행한 경우 make_report.py의 실험 환경 설명도 수정해야 합니다.

## 제출 절차

1. 제공된 ZIP을 컴퓨터에서 압축 해제합니다.
2. 교수님 환경 저장소 https://github.com/lec-algorithm/algorithm-env 의 Use this template > Create a new repository로 본인 저장소를 만듭니다.
3. 내 저장소의 Add file > Upload files로 이 패키지의 src, tests, report, tools 폴더와 Makefile, README.md 등 파일을 올립니다. src/sort.h 및 sort.c를 포함하여 같은 경로 파일을 교체합니다. 템플릿의 Python 예제는 이 Makefile에서 사용하지 않습니다.
4. Codespaces를 열어 저장소 루트에서 make test를 실행하고 통과하는지 확인합니다.
5. 본인 저장소의 주소를 보고서 마지막 URL 칸에 넣고 PDF를 저장합니다. 또는 위 생성 명령으로 URL을 포함한 PDF를 다시 만듭니다.
6. URL이 포함된 PDF를 저장소 report에도 반영합니다.
7. **내 GitHub 저장소에서 Code > Download ZIP으로 다시 받은 ZIP**을 코드 제출물로 사용합니다. 제공된 패키지 ZIP은 업로드 준비용이며 GitHub에서 내려받은 제출 ZIP을 대신하지 않습니다.
8. PDF 보고서와 GitHub에서 받은 ZIP을 제출합니다. 저장소가 교수님께 공개 또는 접근 가능해야 합니다.

학번·이름, 세 알고리즘의 설명, 결과 및 AI 사용 범위를 확인한 후 제출하세요. 보고서에 지정된 GitHub 저장소: https://github.com/kjgdl2525-gi/sorting-hw1

## 검증

- 624개 정확성, 경계값, 안정성 및 카운터 검사 통과.
- 60개 실험 조건 행, 조건마다 5회 측정과 1회 예열, 별도 통계 실행.
- 측정마다 qsort와 키 대조 및 original 태그를 이용한 원소 보존 확인.
- ASan 및 UBSan 통과. 실행 환경 제약 때문에 LeakSanitizer는 끄고 실행했습니다:

```sh
ASAN_OPTIONS=detect_leaks=0 make sanitize
```

## 참고 및 AI 사용

교수님 템플릿과 샘플의 구조를 참고하되 코드는 별도로 작성하였습니다. 힙 정렬 설명, 코드·검증·실험·분석 및 보고서 작성에 ChatGPT를 사용했습니다. PDF에 사용 범위를 명시했습니다.

Nanum Gothic은 SIL Open Font License로 재배포하며 tools/OFL.txt에 라이선스가 있습니다.
