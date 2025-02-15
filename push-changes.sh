#!/bin/bash

git fetch origin $(git rev-parse --abbrev-ref HEAD)
clang-format --Werror -style=file -i src/*.cpp include/*.h 
git add --interactive
echo "Specify commit message:"
read commit_message
git commit -m "$commit_message"
git push