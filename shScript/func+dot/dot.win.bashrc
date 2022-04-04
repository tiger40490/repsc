# prefer source to dot

source $HOME/append.bashrc_win.txt
#source $HOME/append.bashrc_XYZ.txt
### code below is Not part of append.bashrc_win
exa /c/0/repo1
exa /c/0/repo1/blog
type gg #showcase
pwd | grep repo1 
[[ "$?" == "0" ]] || cd $prj
df -h --output=avail /

printf "done sourcing append.bashrc at SHLVL = $SHLVL"
