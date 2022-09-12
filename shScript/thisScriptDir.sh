dirname "${BASH_SOURCE[0]}"
echo .. above dirname is often a relative path
#
fullpath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo fullpath is $fullpath # fairly reliable one-liner, provided the script itself is not a symlink

# readlink -f $0 # requires more steps, but takes care of symlinks. Seldom needed.
