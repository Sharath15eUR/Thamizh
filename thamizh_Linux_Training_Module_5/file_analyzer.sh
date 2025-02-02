#!/bin/bash

error="error.log"
> "$error"
log_error()
{
	echo "[ERROR] $1" | tee -a "$error"
}

search_dir()
{
	local DIR="$1"
	local KEYWORD="$2"
	

	if [[ ! -d "$DIR" ]]; then
		log_error 'Directory "$DIR" does not exist'; return;
	fi

	for file in  "$DIR"/*; do

		if [[ -d "$file" ]]; then
			search_dir "$file" "$KEYWORD"
		fi
		if [[ -f "$file" ]]; then
			grep -Hn "$KEYWORD" "$file"
		fi
	done
}


validate_keyword()
{
	local KEYWORD="$1"

	if [[ ! "$KEYWORD" =~ ^[a-zA-Z0-9_]+$ ]]; then
		log_error "Invalid keyword $KEYWORD"; exit 1;
	fi
}

display_help()
{
	cat <<-EOF
	Usage: "$0" [OPTIONS]
OPTIONS:
	-d <directory> Search for  keywords in a directory
	-f <file> Search for keywords in a file
	-k <keyword> Keyword to be searched
	--help displays the help information
EOF
}


while getopts ":d:f:k:-:" opt;do
	case "$opt" in
	  d) SEARCH_DIR="$OPTARG" ;;
	  f) SEARCH_FILE="$OPTARG" ;;
	  k) KEYWORD="$OPTARG" ;;
	  -)
		case "${OPTARG}" in
		  help) display_help; exit 0 ;;
		  *) log_error "Invalid options: $OPTARG"; exit 1 ;;
		esac
		;;
	  ?) log_error "Invalid options: $OPTARG"; exit 1 ;;
	esac
done

if [[ -z "$KEYWORD" ]]; then
	log_error "Keyword is required"; exit 1;
fi



validate_keyword "$KEYWORD"

if [[ -n "$SEARCH_DIR" && -n "$SEARCH_FILE" ]]; then
	log_error "Cannot use both -d and -f at the same time"; exit 1;

elif [[ -n "$SEARCH_DIR" ]]; then
	
	search_dir "$SEARCH_DIR" "$KEYWORD"

elif [[ -n "$SEARCH_FILE" ]]; then
	if [[ ! -f "$SEARCH_FILE" ]]; then
		log_error "$File not found"; exit 1;
	fi
	grep -Hn "$KEYWORD" <<< $(cat "$SEARCH_FILE")
else
	log_error "Either -f or -d must be used. Use --help for help"; exit 1;
fi
