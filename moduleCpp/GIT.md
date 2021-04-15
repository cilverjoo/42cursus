 2186  git config --global --edit
 2187  git commit --amend --reset-author
 2188  git push origin master:main


## 특정 커밋으로 repository를 reset하고 싶을 때
 git checkout 8bf0013dcf3bdfdd004d78336d875a8eb6ae92e0 . 또는
 git reset --hard 196bf17dce917e35fae7cadbb2b2a0886f4dbd53 (해당 커밋 이후의 내용을 취소)


## git push origin master
## git push
Working tree에 있던 파일들의 수정 내역을 인덱스에 staging하고, staged 파일들을 commit하고 나면 이 변경 이력은 로컬 저장소에 반영됩니다. 이 변경 이력들을 원격 저장소(remote)에 공유하려면, push를 사용하면 됩니다.
이 커맨드에서 origin은 원격 저장소(remote)의 주소를 뜻하고, master는 현재 브랜치를 뜻합니다.


## git push origin master:main
- 원격저장소에 현재 브랜치의 내용을 반영하되 main branch에 반영하겠다!!


## rebase로 병합하기
- 'issue3' 브랜치로 전환하여 'master' 브랜치에 rebase 를 실행합니다.

	git rebase master
	git add myfile.txt
	git rebase --continue 

// rebase 만 실행한 경우에는 위의 그림처럼 'issue3' 브랜치가 두 브랜치의 앞 쪽으로 위치가 옮겨졌을 뿐 'master' 브랜치는 아직 'issue3'의 변경 사항이 적용되지 못한 상태로 뒤에 남겨져 있습니다	
//rebase 의 경우 충돌 부분을 수정 한 후에는 commit 이 아니라 rebase 명령에 --continue 옵션을 지정하여 실행해야 합니다.

- issue3 브랜치에 변경하고 싶은 내용을 저장한 후에는 master 브랜치로 이동하여 병합을 시도하면 된다.

	git checkout master
	git merge issue3

출처 : https://backlog.com/git-tutorial/kr/stepup/stepup2_8.html
