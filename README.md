# Kof_Copy_Project

## Title : 킹오파(The King of Fighter's) copy by 성진짱

> ####  장르 : 대전, 액션
> ####  개발 : 팀개발(3인)
> ####  플렛폼 : PC
> ####  사용 프로그램 : WinAPI, Visual C++
> ####  제작 기간 : 20.05.7 ~ 20.05.13 제작(21.07.25 깃허브 커밋)
> ####  간단 설명 : WinAPI를 활용한 첫 팀 프로젝트. 킹오브파이터즈 게임을 재현. 


## 기능 구현 및 클래스 설명

> + 기능 구현
>   + 컨트롤(Control)
>     + 이동 및 공격(선택)
>     + ~~스킬(미구현)~~
>   + ~~캐릭터 선택(3종의 플레이어블 캐릭터 및 캐릭터 선택창 구현)(팀원개발)~~
>   + ~~카메라~~
>     + ~~BackBuffer를 활용. 1P, 2P간 위치 변경 시에도 카메라 워크 조정~~
>   + 히트박스 및 피격 박스, 판정
>     + 기본 자세 및 공격과 이동, 쌍방의 이동간 피격박스 체크를 통한 밀림 등 이동간 판정 구현
>     + 공격 프레임간 프레임별 히트박스의 크기 변경 및 피격 판정 구현
>     + 딜레이 프레임(시전 전, 시전 중, 시전 후) 
>   + UI
>     + 체력 바
>     + ~~타이머(팀원개발)~~
>   + 기타
>     + 6종의 인게임 백그라운드 임의 재생
>     + ~~캐릭터 이동에 따른 카메라 이동(화면 크기 이상의 백그라운드) 및 기타 처리(팀원 개발)~~.
## 프로젝트 구조
  + 시스템 디자인
    ![System_Kof](https://user-images.githubusercontent.com/63716789/127965831-0a58f9e0-2af9-460d-837c-0494971dc392.jpg)
  + 중요 코드
    + 히트박스
      <p align="center"><img src="https://user-images.githubusercontent.com/63716789/127970141-8397fd4b-ad06-4c19-9e36-26b69d814046.JPG"></p>
      
      + 캐릭터간 공격판정에는 선딜레이, 공격딜레이, 후딜레이 3가지 딜레이 판정이 존재합니다.
      + 선딜레이는 공격키 입력 후 히트박스가 생성되기 이전 프레임이며 공격 애니메이션이 발동 중이나 공격 판정이 이루어지지 않습니다.
      + 공격딜레이는 히트박스가 존재하는 타이밍이며 피격박스 범위 판정내에 있는지 체크한 뒤 이에 따른 판정이 이루어집니다.
      + 후딜레이 역시 선딜레이 처럼 히트박스가 사라진 이후이며 공격 애니메이션이 발동중이나 공격판정이 이루어지지 않습니다.
    + 피격판정
      ![damaged_1](https://user-images.githubusercontent.com/63716789/127966488-b8849921-3235-418f-b510-6d0dc32c378a.JPG)
      + 피격 박스는 공격 간 히트 판정에 필요한 데이터 값으로써, 1p와 2p클래스의 FRECT형 매개변수로 사용되었습니다.(FRECT는 float타입의 RECT 구조체 데이터를 가진 구조체.)
      + 게임 시작 후, 대결 화면이 출력됨과 동시에 출력되고, 캐릭터간 신장 차이로 인하여 각자 고유의 히트박스 크기를 가지고 있습니다.
      + 동작간 피격박스가 달라지는 경우가 있으며, 바뀌는 프레임에 대하여 따로 크기를 변경해주고, 동작이 끝나는 시점에서 다시 초기값의 히트박스로 설정됩니다. 
      ![damaged_2](https://user-images.githubusercontent.com/63716789/127967252-c56736c8-bff4-4ca5-9b78-5abe50ad78bb.JPG)
      + 피격 박스는 상시 캐릭터의 위치 값을 기준으로 업데이트 되며, 상대방의 공격 판정에 의해 히트 박스의 좌표가 피격 박스 내에 존재할 시에 피격 판정이 성립됩니다.
      + 피격 판정 시 캐릭터의 hp가 일정 수준 감소하며 캐릭터의 위치 값이 상대방 기준 반대방향으로 10 pixel 이동됩니다.(밀려난다) 이 때 밀려난 위치 값이 화면 출력 범위를 벗어나게 되면 캐릭터의 위치 값은 벽으로 지정된 위치 값을 기준으로 이동(보정)처리되며, 밀려나면서 피격 모션이 재생됩니다.
      <p align="center"><img src="https://user-images.githubusercontent.com/63716789/127968142-9d196ad3-1223-4f1d-8438-e8edab021cfa.jpg"></p>
      <div align="center"> <사진첨부 - 게임화면(파란박스(피격박스),빨간박스(히트박스),녹색박스(벽))>
    + 이동판정
      ![movement](https://user-images.githubusercontent.com/63716789/127968542-04732fcb-74f6-43e2-ab30-5bec61513251.JPG)
      + 캐릭터는 이동 키를 누른 시점으로 부터 이동키가 떼어질 때까지 이동 방향키 방향을 기준으로 3pixel씩 이동하게 처리되어있습니다.
      + 캐릭터 이동 방향간 상대방 캐릭터가 존재할 시, 상대방의 캐릭터 위치값 또한 동일한 값으로 이동 처리됩니다.
      + 상대방 캐릭터가 화면출력 범위(벽)을 벗어나게 되면, 위치값은 화면 출력 범위내로 보정되고 본인캐릭터 역시 이동 값은 변화하지 않지만 관련 애니메이션은 재생됩니다.
      + 상대방의 캐릭터와 마주보는 상태에서 서로 이동방향이 상대방의 맞은편을 향하게 되는 경우, 서로 이동 값은 변화하지 않고 관련 애니메이션만 재생됩니다.
      + 캐릭터의 후진 역시 화면출력 범위(벽)을 벗어나게 되면 위의 방식으로 동일하게 처리됩니다.
