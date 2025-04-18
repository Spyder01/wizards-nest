#!/usr/bin/env python3
from PIL import Image
import sys

def remove_border(img):
    """
    Remove uniform border from an image.
    
    Assumes the border color is the pixel in the top-left corner.
    """
    # Get image dimensions and border color from top-left pixel
    width, height = img.size
    border_color = img.getpixel((0, 0))
    
    # Initialize crop boundaries
    left, top, right, bottom = 0, 0, width, height
    
    # Find top boundary
    for y in range(height):
        for x in range(width):
            if img.getpixel((x, y)) != border_color:
                top = y
                break
        else:
            continue
        break

    # Find bottom boundary
    for y in range(height - 1, -1, -1):
        for x in range(width):
            if img.getpixel((x, y)) != border_color:
                bottom = y + 1  # Include this row
                break
        else:
            continue
        break

    # Find left boundary
    for x in range(width):
        for y in range(height):
            if img.getpixel((x, y)) != border_color:
                left = x
                break
        else:
            continue
        break

    # Find right boundary
    for x in range(width - 1, -1, -1):
        for y in range(height):
            if img.getpixel((x, y)) != border_color:
                right = x + 1  # Include this column
                break
        else:
            continue
        break

    # Crop the image to the detected region
    cropped = img.crop((left, top, right, bottom))
    return cropped

def main():
    if len(sys.argv) != 3:
        print("Usage: python remove_border.py input.png output.png")
        sys.exit(1)

    input_path, output_path = sys.argv[1], sys.argv[2]
    
    try:
        img = Image.open(input_path).convert("RGBA")
    except Exception as e:
        print(f"Error opening image: {e}")
        sys.exit(1)
    
    cropped_img = remove_border(img)
    try:
        cropped_img.save(output_path)
        print(f"Cropped image saved to {output_path}")
    except Exception as e:
        print(f"Error saving image: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()

