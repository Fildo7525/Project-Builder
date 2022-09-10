#compdef buildProject

# simplest way takes arguments from --help command
# compdef _gnu_generic buildProject

args=( \
	{-h,--help}:"Print help" \
	{--type,-t}:"Define project language" \
	{--no-git,-g}:"Prohibit default git repozitory initialization" \
	{--qt5,-q}:"Link qt5 to your C++ project" \
	{--opencv,-c}:"Link OpenCV to your C++ project" \
	{--maven,-m}:"Use maven as Java build system" \
	"--rpi:Link WiringPi to your C++ project" \
	"--list-languages:List all currently supported languages" \
	"--list-completion:List all supported commands" \
)

_arguments \
	'--type[Define project language args]:filetype:->type' \
	'-t[Define project language args]:filetype:->type' \
	'*:project name:'

case "$state" in
	type)
		local -a ft
		ft=($(buildProject --list-languages))
		_multi_parts / ft
		;;
	*)
		;;
esac

_describe 'buildProject' args
