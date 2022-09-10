_compadd() {
	COMPREPLY=($(compgen -W "$1" -- "$cur"))
}

_main() {
	# complete current word even if it is not command
	case "$cur" in
		-*)
			_compadd "$(buildProject --list-completion)"
			;;
		*)
			_compadd "$(buildProject --list-languages)"
			;;
	esac
}
_wrap_main() {
	local -a words
	local cword cur

	words=("${COMP_WORDS[@]}")
	cword=$COMP_CWORD
	cur="${words[cword]}"

	_main

}

complete -F _wrap_main buildProject
