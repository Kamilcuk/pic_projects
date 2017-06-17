#!/bin/bash -eu
set -o pipefail
############################# fucntions ###################

sed_args=() # global variable, exported from functions
# sed regexes
rgx_preline='[[:space:]]*[[:digit:]]\+[[:space:]]'
rgx_precode="$rgx_preline"'[[:space:]][[:xdigit:]]\{6\}[[:space:]]\{1,2\}'
rgx_precomment="$rgx_preline"';;'
rgx_prefuncdec="$rgx_preline"';;[[:space:]]\*\+[[:space:]]function[[:space:]]'
rgx_postfuncdec='[[:space:]]\*\+'
rgx_Cfuncname='[a-zA-Z0-9_]\+'
rgx_prefuncname='\(i1\|i2\|\)'
rgx_anyfuncname="$rgx_prefuncname"'_'"${rgx_Cfuncname}"
rgx_anyfuncstart="^${rgx_prefuncdec}\(${rgx_anyfuncname}\)${rgx_postfuncdec}$"
rgx_code1="$rgx_precode"'[[:xdigit:]]\{4\}'
rgx_code2="$rgx_precode"'[[:xdigit:]]\{4\}[[:space:]]\{1,2\}[[:xdigit:]]\{4\}[[:space:]]\+'


rgx_all_func_names() {
	# args: function_names
	echo -n "${rgx_prefuncname}_\("
	echo -n "$1";
	shift;
	printf "%s" "${@/#/\\|}";
	echo -n "\)"
}

sed_args_list() {
	local f
	# args: function_names
	f=$(rgx_all_func_names "$@")
	sed_args=(
		"-n"
		"-e"
"/^${rgx_precode}[[:space:]]\+${f}:\$/,"\
"/^${rgx_precode}[[:space:]]\+__end_of${f}:\$/{"\
"/^${rgx_precode}[[:space:]]\+__end_of${f}:\$/G;p;}"
)
}

sed_args_listlong() {
	local f
	# args: function_names
	f=$(rgx_all_func_names "$@")
	sed_args=(
		"-n"
		"-e" 
"/^${rgx_prefuncdec}${f}${rgx_postfuncdec}\$/,"\
"/^${rgx_prefuncdec}${rgx_anyfuncname}${rgx_postfuncdec}\$/p"
	)
	export sed_args
}

sed_args_listcode() {
	local f
	# args: function_names
	f=$(rgx_all_func_names "$@")
	sed_args=(
		"-n"
		"-e" 
"/^${rgx_precode}[[:space:]]\+${f}:\$/{
	:a;
	/^${rgx_precode}[[:space:]]\+__end_of${f}:\$/{
		q;
	}
	/^${rgx_code1}/{
		p;
	}
	n;
	ba;
}"
	)
	export sed_args
}

sed_args_funcs() {
	sed_args=(
		"-n"
		"-e" 
"/^${rgx_prefuncdec}${rgx_anyfuncname}${rgx_postfuncdec}\$/s"\
"/^${rgx_prefuncdec}\(${rgx_anyfuncname}\)${rgx_postfuncdec}\$/\1/p"
	)
	export sed_args
}

sed_args_Cfuncs() {
	sed_args=(
		"-n"
		"-e" 
"/^${rgx_prefuncdec}${rgx_prefuncname}"'_'"${rgx_Cfuncname}${rgx_postfuncdec}\$/s"\
"/^${rgx_prefuncdec}${rgx_prefuncname}"'_'"\(${rgx_Cfuncname}\)${rgx_postfuncdec}\$/\2/p"
	)
	export sed_args
}

sed_args_digraph() {
	sed_args=( "
/${rgx_anyfuncstart}/{
	s/${rgx_anyfuncstart}/\1 ->/;
	h;
	: notcalls;
	n;
	/^${rgx_precomment} This function calls:\$/{
		: functioncalled;
		n;
		/^${rgx_precomment}[[:space:]][[:space:]]\+/{
			s/^${rgx_precomment}[[:space:]]\+//;
			/^Nothing$/{
				d;
			}
			s/\$/;|/;
			G;
			s/\n//;
			s/\(.*\)|\(.*\)/\2 \1/;
			p;
			b functioncalled;
		};
		d;
	}
	b notcalls;
}" )
	export sed_args
}

############################ job functions #####################3

do_mode_listlen2() {
	for f in $(all_func_names "$@"); do
		sed_args=(
				"-e" 
"/^${rgx_precode}[[:space:]]\+${f}:\$/,"\
"/^${rgx_precode}[[:space:]]\+__end_of${f}:\$/p"
		)
		func=$(sed -n "${sed_args[@]}" "${files[@]}")
		if [ -z "$func" ]; then
			continue
		fi
		buff=$(sed -n -e "/^${rgx_code1}/p" <<<"$func")
		single=$(wc -l <<<"$buff")
		double=$(echo "$buff" | sed -n -e "/^${rgx_code2}/p" | wc -l)
		echo "$((single+double)) $f"
	done | { $SORT && sort -h || cat; }
}

do_mode_listlen() {
	# args: function_names
	local f
	f=$(rgx_all_func_names "$@")
	sed -n -e \
"/^${rgx_precode}[[:space:]]\+${f}:\$/{
	s/^${rgx_precode}[[:space:]]\+\(${f}\):\$/\1 /
	h;
	:a;
	n;
	/^${rgx_precode}[[:space:]]\+__end_of${f}:\$/{
		g;
		s/\n//g;
		p;
		d;
	}
	/^${rgx_code1}/{
		/^${rgx_code2}/{
			s/.*/1/;
			H;
		}
		s/.*/1/;
		H;
	}
	ba;
}" "${files[@]}" | while IFS=' ' read -r func rest; do
		echo "$(echo -n "$rest" | wc -c) $func";
	done
}

do_graph_depth() {
	# from https://stackoverflow.com/questions/29320556/finding-longest-path-in-a-graph
	local temp
	temp="$(
		main_do_mode digraph | sed 's/^\([0-9A-Za-z_]*\) -> \([0-9A-Za-z_]*\);$/["\1","\2"],/'
	)"
	python -c '
from collections import *;

def DFS(graph,current,visited,cpath):
	npath = [] #new path
	for node in graph[current]:
		if node not in visited:
			visited.append(node)
			tpath = cpath + [node] #tmp path
			npath.append(tpath)    #append to existing path
			#extend current path
			npath.extend(DFS(graph,node,visited,tpath))
	return npath
def do_DFS(G, root):
	# Run DFS, compute metrics
	all_paths = DFS(G,root,[root],[root])
	max_len   = max(len(p) for p in all_paths)
	max_paths = [p for p in all_paths if len(p) == max_len]
	# Output
	#print("All Paths:"); print(all_paths);
	#print("Longest Paths:"); for p in max_paths: print("  ", p);
	#print("Longest Path Length:"); print(max_len);
	print("%3d %s" % (max_len, root));
	for p in max_paths: print("  ", p);

def find_roots(G):
	roots=[];
	for k,v in G.items():
		found = True;
		for k2,v2 in G.items():
			if k in v2:
				found = False;
				break;
		if found:
			roots.append(k)
	return roots


# Define graph by edges
edges = [
'"${temp}"'
]
G = defaultdict(list)
# Build graph dictionary
for (s,t) in edges:
    G[s].append(t)
for root in find_roots(G):
	do_DFS(G, root)
'
}

do_mode_listlenhistory() {
	# options passed via global variables
	ADDPLUSSIGN=${ADDPLUSSIGN:-true}
	FILTERDIFFS=${FILTERDIFFS:-true}
	PRINTDIFFS=${PRINTDIFFS:-true}
	USEDATEFROMFILE=${USEDATEFROMFILE:-true}
	DATEFROMFILE=${DATEFROMFILE:-.obj/main.hex}
	PRINTVALWITHDIFF=${PRINTVALWITHDIFF:-true}

	# options passed via command line
	local maxtimes statefile
	maxtimes="${1:-10}"
	statefile="${2:-.obj/lstparse_statefile.sqlite3}"

	if [ "$maxtimes" = "clean" ]; then
		echo "Cleaning statefile=${statefile}!"
		rm -f "${statefile}"
		return;
	fi
	
	dodb() { sqlite3 "$statefile" "$(echo "$@" | sed 's/^[[:space:]]\+//')"; }
	if $DEBUG; then
		eval "$(echo "dodb_real()"; declare -f dodb | tail -n +2)"
		dodb() { (set -x; dodb_real "$@";) | tee >(cat >&2); }
	fi

	local listlen now insertnewvalues dodb lastvalues i lastnumdates lastdate allfunctions f vals IFS
	if [ "$maxtimes" -ne "$maxtimes" ] >/dev/null; then
		error "Error numtimes is not a number"
		exit 1
	fi

	{
		# recreate tables if not exist
		dodb '
			CREATE TABLE IF NOT EXISTS listlendates (
				date INTEGER PRIMARY KEY
			);
			CREATE TABLE IF NOT EXISTS listlenhistory (
				date INTEGER, func TEXT, len INTEGER,
				FOREIGN KEY(date) REFERENCES listlendates(date)
			);
		'
	}

	{
		local listlen lastdate filedate lastvalues
		# insert new data only if needed
		dodb_insertnewvalues() {
			# uses global variable listlen
			local now insertnewvalues
			if $USEDATEFROMFILE && [ -e "$DATEFROMFILE" ]; then
				log "new values into database - date from file"
				now=$(stat -c %Y "$DATEFROMFILE")
			else
				log "new values into database - date now"
				now=$(date +%s)
			fi
			dodb "$(
				echo "BEGIN TRANSACTION;"
				echo "INSERT INTO listlendates (date) VALUES ($now);"
				while IFS=' ' read -r n f; do
					echo "INSERT INTO listlenhistory (date,func,len) VALUES ($now,\"$f\",$n);"
				done <<<"$listlen"
				echo "COMMIT;"
			)"
		}
		# insert current values - if needed
		if [ "$(dodb 'select count(*) from listlendates;')" -eq 0 ]; then
			# no values in database - insert new
			listlen=$(SORT=false main_do_mode listlen "$@" | sed 's/[[:space:]]\+/ /g' | sort -h)
			dodb_insertnewvalues
		else
			while :; do # do{ }while(0)
				lastdate=$(dodb 'select max(date) from listlendates;')

				if $USEDATEFROMFILE; then
					if [ ! -e "$DATEFROMFILE" ]; then
						error "File DATEFROMFILE=$DATEFROMFILE does not exists!"
					else
						filedate=$(stat -c %Y "$DATEFROMFILE")
						if [ "$lastdate" -eq "$filedate" ]; then
							log "last compile time equal"
							break;
						fi
					fi
				fi

				# insert new values only if they differ from the last ones
				listlen="$(SORT=false main_do_mode listlen "$@" | \
						sed             -e 's/[[:space:]]\+/ /g' | sort -h)"
				lastvalues="$(dodb "select len,func from listlenhistory	where date = '$lastdate';" | \
						sed -e 's/|/ /' -e 's/[[:space:]]\+/ /g' | sort -h)"
				if [ -z "$lastvalues" ]; then
					error "lastvaules are empty!"
					error "Attemping to fix that."
					dodb 'delete from listlendates where date = (select max(date) from listlendates);'
					error "Rerun script!"
					exit 1;
				fi
				if [ "$lastvalues" == "$listlen" ]; then
					log "values in database"
					break;
				fi

				dodb_insertnewvalues
			break; done;
		fi
	}


	{
		local lstnumdates firstdate allfunctions 
		# pre display - some variables
		lastnumdates=($(
			dodb "select date from listlendates order by date ASC limit $maxtimes;"
		))
		firstdate=$(head -n 1 <<<"$lastnumdates")
		allfunctions=($(
			dodb "select distinct func from listlenhistory where date >= '$firstdate' order by func ASC;"
		))
		if [ "${#lastnumdates[@]}" -eq 0 ]; then
			error '"${#lastnumdates[@]}" -eq 0 ' "WTF?"
			exit 1;
		fi
		if [ "${#allfunctions[@]}" -eq 0 ]; then
			error '"${#allfunctions[@]}" -eq 0' WTF
			exit 1;
		fi
	}

	# simple output header
	echo "funcname$(for d in "${lastnumdates[@]}"; do echo -n " $(date --date=@$d +%T)"; done)"
	echo "---$(for d in "${lastnumdates[@]}"; do echo -n " ---"; done)"
	{
		local f vals allowprint diffs lastval nextval vals val diffscopy d 
		# for every function - line in output
		for f in "${allfunctions[@]}"; do

			# for every date - column in output

			# get length values from database
			vals=($(dodb "select len from listlenhistory where date >= '$firstdate' and func = '$f';"))
			if [ "${#vals[@]}" -ne "${#lastnumdates[@]}" ]; then
				# when some values are missing (the function was missing in some compiles) 
				# we get less numbers then expected
				# we need to do vals one by line, and fills missing ones with zeros
				vals=()
				# fill vals with length from database
				for date in "${lastnumdates[@]}"; do
					# get next value
					newval="$(dodb "select len from listlenhistory where date = '$date' and func = '$f';")"
					# some sanity
					if   [ -z "$newval" ]; then # catch missing values
						newval=0;
					elif [ "$newval" -eq "$newval" ] 2>/dev/null; then
						:;
					else
						error "newval is not a number!"
						exit 1
					fi
					# add this values to values
					vals+=("$newval")
				done
			fi

			while :; do #do{
				if $PRINTDIFFS && [ "${#vals[@]}" -gt 1 ]; then
					local diffs lastval val allowprint diffscopy val1
					diffs=()
					lastval="${vals[0]}"
					for val in "${vals[@]:1}"; do 
						nextval=$((val - lastval))
						diffs+=("$nextval");
						lastval="$val"
					done

					if $FILTERDIFFS; then
						# print only, when all of diffs numbers are zero
						if [ -z "$(printf "%s" "${diffs[@]//0/}")" ]; then
							break; # out of while
						fi
					fi

					if $ADDPLUSSIGN; then
						# add '+' sign to every positive number
						diffscopy=("${diffs[@]}")
						diffs=()
						for d in "${diffscopy[@]}"; do
							if [ "$d" -gt 0 ]; then
								diffs+=("+$d")
							else
								diffs+=("$d")
							fi
						done
					fi

					if $PRINTVALWITHDIFF; then
						for i in $(seq 0 $((${#diffs[@]}-1))); do
								diffs[$i]="${vals[$((i+1))]}(${diffs[i]})"
						done
					fi

					vals=("${vals[0]}" "${diffs[@]}")
				fi

				# print this line
				echo "$f ${vals[*]}"

			break; done; #}while(0)
		done
	}
}
############################# common functions #####################

log() { if $VERBOSE; then echo "> " "$@" >&2; fi; }
error() { echo "ERROR" "$@" >&2; }

usage() {
	local name
	name=$0
	cat <<EOF
USAGE:
      $name -h
      $name [OPTIONS] <MODE> [MODE ARGS]

Program displays various infomations from .lst files generated by Microchip's xc8 compiler.

OPTIONS:
    -f <file.lst>                  - add file to parse, file is in lst format
    -d <dir with *.lst files>      - parse all files in directory that end with *.lst
    -Q                             - less vebose output
    -V                             - more verbose output
    -D                             - debug mode
    -h                             - print this text and exit
    -s                             - sort/beauty output
    -N                             - don't sort/beauty output
    -k                             - when listing function bodies, remove line numbers and code numbers
                                     usufull for listcode to see only function code
    -M                             - measure execution speed using ttic.sh and ttoc.sh commands


MODEs:
    list     [<function name>,...] - list body of specified function names
    listlong [<function name>,...] - same as list, but more comments
    listcode [<function name>,...] - same as list, but only lines with assembly
    listlen  [<function name>,...] - print instruction count of functions
    funcs                          - list all functions
    Cfuncs                         - print all functions as declared in C sources
    digraph                        - print digraph used to generate callgraph
    callgraph <.png file>          - generate call graph of functions
    graph_depth                    - give some info about graph depth information
    listlen2 [<function name>,...] - slower listlen version, left for reference
    listlenhistory [times] [statefile] - print changes in length of functions
                                         times, default: 10
                                         statefile, default: .obj/lststatefile
    listlenhistory clean   [statefile] - remove statefile

if none of -f and -d options are given, then option '-d .obj' is assumed.
If function names are ommitted, all functions are used.

Examples:
      $name -d .obj list SYS_InterruptHigh
      $name list SYS_InterruptHigh
      $name funcs
      $name listlong main 'SYS*'
      $name Cfuncs
      $name listlen
      $name listcode main 'SYS*'

Written by Kamil Cukrowski (c) 2017. Under MIT license.
EOF
}

############################## main ########################

if [ $# -eq 0 ]; then usage; exit 1; fi

# getopts
files=() OPTIONS=() VERBOSE=false DEBUG=${DEBUG:-false} mode="" 
SORT=true SPEEDMEASURE=false REMOVELINENUMBERS=false
args=$(getopt -o f:d:QVDhNMNk -- "$@")
eval set -- "$args"
while true; do
	case "${1/#-/}" in
		f) files+=("$2"); shift; ;;
		d) files+=($(find "$2" -name '*.lst')); shift; ;;
		Q) VERBOSE=false; ;;
		V) VERBOSE=true; ;;
		D) DEBUG=true; set -x; ;;
		h) usage; exit 0; ;;
		s) SORT=true; ;;
		N) SORT=false; ;;
        k) REMOVELINENUMBERS=true; ;;
		M) SPEEDMEASURE=true; ;;
		-) shift; break; ;;
		*) error "Bad argument $1"; exit 1; ;;
	esac
	shift
done
mode="$1"
shift

if $DEBUG; then set -x; fi
if $SPEEDMEASURE; then ttic.sh $$; fi

# check input
if [ -z "${files[*]}" ]; then
	if [ -d .obj ]; then
		files=($(find .obj -name '*.lst'))
	fi
fi
if [ -z "${files[*]}" ]; then
	error ".obj directory not found."
	error "No input *.lst files given"
	exit 1;
fi
for f in "${files[@]}"; do
	if [ ! -e "$f" ]; then
		ERROR "$f not readable"
		exit 1
	fi
done

tempfile=$(mktemp) # global tempfile variable
trap 'rm -f $tempfile' EXIT

############ main work - switch on mode ############
main_do_mode_functions_arguments() {
	# args - function names
	local opt stars
	stars=()
	functions=() # global variable
	if [ $# -eq 0 ]; then
		#error "Mode $mode takes function names as arguments";
		#exit 1;
		set -- "*"
	fi
	for opt in "$@"; do
		if   expr "$opt" : '^[0-9a-zA-Z_]\+$' >/dev/null; then 
			functions+=("$opt")
		elif expr "$opt" : '^[0-9a-zA-Z_\*]\+$' >/dev/null; then 
			stars+=("${opt//'*'/'.*'}")
		else
			error "Function name \"$opt\" is not allowed by C standard!";
			exit 1;
		fi
	done
	if [ -n "${stars[*]}" ]; then
		functions+=($(egrep "^$(IFS='|'; echo "${stars[*]}";)$" <(SORT=true main_do_mode Cfuncs)))
	fi
	IFS=$'\n' functions=($(sort -u <<<"${functions[*]}"))
	log "Searching for functions: ""${functions[@]}"
	if [ -z "${#functions[*]}" ]; then
		error "No functions found!"
		exit 1;
	fi
	export functions
}
main_do_mode() {
	local mode functions
	mode=$1
	shift
	case "$mode" in
	Cfuncs|funcs)
		eval "sed_args_${mode}"
		sed "${sed_args[@]}" "${files[@]}" | { if $SORT; then sort -u; else cat; fi; }
		;;
	list|listlong|listcode)
		main_do_mode_functions_arguments "$@"
		eval "sed_args_${mode}" "${functions[@]}"
		sed "${sed_args[@]}" "${files[@]}" | \
			{ if $REMOVELINENUMBERS; then sed "s/^${rgx_precode}[[:xdigit:]]\{4\}[[:space:]]\{1,2\}\([[:xdigit:]]\{4\}\)\?[[:space:]]\+//"; else cat; fi; }
		;;
	listlen)
		main_do_mode_functions_arguments "$@"
		do_mode_listlen "${functions[@]}" | { if $SORT; then sort -h | column -t -s' '; else cat; fi; }
		;;
	listlen2)
		main_do_mode_functions_arguments "$@"
		do_mode_listlen2 "${functions[@]}" | { if $SORT; then sort -h | column -t -s' '; else cat; fi; }
		;;
	listlenhistory)
		do_mode_listlenhistory "$@" | \
			{ if $SORT; then sed 's/^/# /' | rev | column -t -s' ' -o' ' | rev | sed 's/^# //';  else cat; fi; }
		;;
	digraph)
		sed_args_digraph
        sed -n -e "${sed_args[@]}" ${files[@]}
		;;
	graph_depth)
		do_graph_depth
		;;
	callgraph)
		if [ $# -eq 0 ]; then error "Mode $mode takes .png file output name"; exit 1; fi
		(
			echo "digraph \"$0 ${files[@]}\" {"
			main_do_mode callgraph_digraph
	       		echo '}' 
		) > $tempfile
		( set -x; 
		dot $tempfile -Tpng -o ${1}
		)
		;;
	*) error "Unknown mode: $mode"; exit 1; ;;
	esac
}

########## substitute '*' in function modes for all passing function
log "Running mode=\"$mode\" with $(case $# in 0) echo -n "arguments:";for i in "$@";do echo -n " \"$i\"";done; ;; *) echo -n "no arguments"; ;; esac)"

############# finally do smth main mode ###########################
main_do_mode "$mode" "$@"

if $SPEEDMEASURE; then echo "Execution time: $(ttoc.sh $$)" >&2; fi
