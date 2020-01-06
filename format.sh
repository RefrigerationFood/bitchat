#!/usr/bin/env bash

#clang-format should be 6th or higher version
GIT_IGNORE=".gitignore"
IGNORE_TARGETS=()
EXTENSIONS=(".cpp" ".hpp")

FILES=()
for EXTENSION in ${EXTENSIONS[@]}; do
  while IFS=  read -r -d $'\0'; do
    FILES+=("$REPLY")
  done < <(find . -name \*${EXTENSION} -print0)
done

if [ -f "${GIT_IGNORE}" ]; then
  echo "*** USE GIT IGNORE ***"

  for LINE in $(cat ${GIT_IGNORE}); do
    LENGTH=${#LINE}
    if [ "${LINE:LENGTH:1}" == "/" ]
    then
      IGNORE_TARGETS+=(${LINE})
    else
      IGNORE_TARGETS+=("${LINE}/")
    fi
  done

  for TARGET in "${IGNORE_TARGETS[@]}"; do
    for i in "${!FILES[@]}"; do
      if [[ "${FILES[i]}" == *"$TARGET"* ]];
      then
        echo "IGNORE: ${FILES[i]}"
        unset 'FILES[i]'
      fi
    done
  done
fi

for FILE in "${FILES[@]}"; do
  echo ${FILE}
  clang-format -i ${FILE}
done