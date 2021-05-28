## cub3D?
cub3d는 레이캐스팅을 이용해 3D 게임을 구현하는 과제입니다. 광선(ray)을 던져(cast) 현재 위치에서 벽(또는 장애물)이 충돌하는 지점을 찾아 거리를 구하는 방식으로 거리에 따라서 벽의 높이를 결정합니다.
3D게임의 시초라 불리는 울펜스타인이 이 방식으로 만들어졌습니다.

## mlx library를 활용하여 창을 띄우고 이미지를 구성하자.
* 이동 키 입력 받기
* xpm 파일 이미지로 변환하기
* 직접 픽셀을 찍어 이미지 만들어보기
* 스프라이트라는 장애물 만들어보기

## raycasting 알고리즘 참고 사이트
https://lodev.org/cgtutor/raycasting.html
번역본 : https://github.com/365kim/raycasting_tutorial

## 플레이 방법

```
  >> make
  >> ./cub3D map.cub
```
