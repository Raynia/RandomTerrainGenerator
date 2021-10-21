# RandomTerrainGenerator
- 제작기간: 2019.03.06 ~ 2019.06.12
- 참가인원: 3명
- 주제: Perlin Noise를 활용하여 OpenGL과 SDL을 기반으로 3D 폴리곤 지형을 생성하고 탐색할 수 있는 생성기
- 본 프로젝트는 Github를 활용하여 개발되지 않았음
- 프로젝트 보존을 위해 팀원들의 동의를 얻어 Github에 등록하였음

# 개발환경
- Visual Studio 2017
- SDL 2
- OpenGL 1.1
- MFC v142 x86

# 실행화면
## 첫 화면
<img src = "https://user-images.githubusercontent.com/46100945/138315399-825a62e8-11b4-4af7-afb9-98dd0c0fb76b.png" width = "854" height = "480">

- 상단의 Create, Save, Open 버튼으로 시드 입력 후 지형 생성, 파일로 저장, 저장된 파일 불러오기 가능
- 우측에서 현재 위치한 좌표값을 확인

## 시드 입력
<img src = "https://user-images.githubusercontent.com/46100945/138315414-f4b325c6-03f7-4f41-b865-f3a5938082c3.png">

- 무작위 문자 및 숫자를 입력하여 시드 지정
 
## 생성된 지형
<img src = "https://user-images.githubusercontent.com/46100945/138315391-03fcc3ed-a0e9-47da-84df-870c0cbc4023.png" width = "854" height = "480">

- 지정된 시드에 따라 3D 폴리곤으로 지형을 생성

## 저장 및 불러오기
<img src = "https://user-images.githubusercontent.com/46100945/138315410-15086066-2cdd-41be-84ad-a0d949fea4a0.png" width = "854" height = "480">
<img src = "https://user-images.githubusercontent.com/46100945/138315406-1514ec1d-dc9c-43f8-bce2-da35cdfc6c76.png" width = "854" height = "480">

- 시드값과 지형 정보를 ter 파일로 저장
- 저장된 파일은 언제든지 불러오기 가능


# 알려진 오류
- 상단의 버튼을 일정 횟수 클릭 시 프로그램이 종료되는 오류
