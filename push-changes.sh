#!/bin/bash

git fetch origin $(git rev-parse --abbrev-ref HEAD)
git add --interactive
echo "Specify commit message:"
read commit_message
git commit -m "$commit_message"
git push