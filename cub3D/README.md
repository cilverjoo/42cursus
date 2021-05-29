# cub3D?
cub3d는 raycasting을 이용해 3D 게임을 구현하는 과제입니다. 3D게임의 시초인 Wolfenstein 3D의 경량버전이라 할 수 있습니다.

raycasting 방식으로 광선(ray)을 던져(cast) 현재 위치에서 벽(또는 장애물)이 충돌하는 지점을 찾아 거리를 구하는 방식으로 거리에 따라서 벽의 높이를 결정하며 미로를 구현합니다.

## 구현 사항
* 이동 키 입력 받기
* xpm 파일 이미지로 변환하기
* 직접 픽셀을 찍어 이미지 만들어보기
* 스프라이트라는 장애물 만들어보기
* --save 옵션을 주면 게임을 시작하지 않고 플레이화면을 비트맵 파일로 저장

<div>
<img width="70%" src="https://user-images.githubusercontent.com/64128985/120070078-2e6dc180-c0c4-11eb-9906-68d878970d19.png">
  </div>
위의 이미지는 cclaude42의 cub3D 플레이 화면임. (참고 : https://github.com/cclaude42/cub3d)


## raycasting 알고리즘 참고 사이트
https://lodev.org/cgtutor/raycasting.html

번역본 : https://github.com/365kim/raycasting_tutorial

## 플레이 방법
> 주의 : cub3D는 42Seoul에서 제공하는 Xlib의 경량 버전인 MiniLibX가 있어야만 플레이 할 수 있습니다.

```
//실행방법
  >> make
  >> ./cub3D map.cub

//비트맵 파일을 만들 때
  >> ./cub3D map.cub --save 
```
* `W` `A` `S` `D` 키로 미로 안을 돌아다닐 수 있습니다.
* 화살표키 `←` `→`를 활용하여 시야를 회전할 수 있습니다.
* 게임을 끝내려면 `ESC`나 `X`를 클릭하면 됩니다.
