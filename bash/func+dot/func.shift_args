# showcase q[ set -- ] construct to replace entire $@
# showcase shift does affect $@
# showcase
# showcase capitalize entire word
# showcase setting an env variable temporarily for one command only

admin(){
  adn=${1^^} ; shift
  set -- $adn "$@"
  echo using adn==$adn, args=="$@"
  HOME=/L/infra   $inmi/epa/bin/adminEPA.sh "$@"
}
