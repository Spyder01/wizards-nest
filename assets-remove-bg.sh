#!/bin/bash

# Directory to search, default is current directory
DIR=${1:-.}

# Recursively find all .png files
find "$DIR" -type f -name '*.png' | while read -r file; do
    echo "Processing $file"
    python3 remove-image-border.py "$file" "$file" || echo "Failed to process $file, skipping..."
done

