# prefer source to dot
source $HOME/append.bashrc_win.txt
#source $HOME/append.bashrc_XYZ.txt
source $HOME/.func.exa.txt
source $HOME/.func.git-rmme.txt

gd2br=main

### code below is Not part of append.bashrc_win
exa /c/0x/repsc
exa /c/0x/repsc/shScript
exa /c/0x/repo1
exa /c/0x/repo1/blog

type 0copy #showcase
pwd | grep repo1
[[ "$?" == "0" ]] || cd $prj
df -h --output=avail /

printf "done sourcing append.bashrc at SHLVL = $SHLVL"
