
.data
//
// Offsets within the Image structure
//
.equ    image_width, 0          // Offset for width (int)
.equ    image_height, 4         // Offset for height (int)
.equ    image_pixels, 8         // Offset for pixels (double *)
.equ    image_struct_size, 16   // Total size of Image struct (aligned to 8 bytes)

.text

.global create_image
//
// void *create_image(int wid, int hit)
// Create an image ADT and return it.
//
create_image:
    // Parameters:
    // w0: wid (width)
    // w1: hit (height)

    // Function prologue
    stp     x29, x30, [sp, #-16]!
    stp     x19, x20, [sp, #-16]!
    stp     x21, x22, [sp, #-16]!

    // Save width and height in 64-bit registers
    uxtw    x19, w0                 // x19 = (uint32_t)wid
    uxtw    x20, w1                 // x20 = (uint32_t)hit

    // Allocate memory for Image struct
    mov     x0, #image_struct_size  // x0 = size of Image struct
    bl      malloc                  // Call malloc(size)
    cbz     x0, create_image_fail   // If malloc returned NULL, fail

    // Store Image struct pointer
    mov     x21, x0                 // x21 = Image struct pointer

    // Store width and height into Image struct
    str     w19, [x21, #image_width]    // Image->width = wid
    str     w20, [x21, #image_height]   // Image->height = hit

    // Calculate number of pixels: num_pixels = wid * hit
    mul     x22, x19, x20           // x22 = wid * hit (64-bit multiplication)

    // Calculate size of pixel data: size = num_pixels * 8
    lsl     x22, x22, #3            // x22 = x22 << 3 (multiply by 8)

    // Allocate memory for pixel data
    mov     x0, x22                 // x0 = size of pixel data
    bl      malloc                  // Call malloc(size)
    cbz     x0, create_image_fail_free     // If malloc failed, free Image struct and fail

    // Store pixel data pointer into Image struct
    str     x0, [x21, #image_pixels]    // Image->pixels = pixel data pointer

    // Return Image struct pointer
    mov     x0, x21                 // x0 = Image struct pointer

    // Function epilogue
    ldp     x21, x22, [sp], #16
    ldp     x19, x20, [sp], #16
    ldp     x29, x30, [sp], #16
    ret

create_image_fail_free:
    // Free the previously allocated Image struct
    mov     x0, x21                 // x0 = Image struct pointer
    bl      free                    // free(Image struct)

create_image_fail:
    // Return NULL
    mov     x0, #0                  // x0 = NULL

    // Function epilogue
    ldp     x21, x22, [sp], #16     // Restore x21 and x22
    ldp     x19, x20, [sp], #16     // Restore x19 and x20
    ldp     x29, x30, [sp], #16     // Restore frame pointer and link register
    ret

    .global destroy_image
//
// void destroy_image(void *image)
// Destroy image, freeing memory
//
destroy_image:
    // Parameters:
    // x0: image pointer

    // Check if image is NULL
    cbz     x0, destroy_image_done  // If image is NULL, nothing to do

    // Load pixel data pointer
    ldr     x1, [x0, #image_pixels] // x1 = image->pixels

    // Check if pixels is NULL
    cbz     x1, skip_free_pixels    // If pixels is NULL, skip freeing pixels

    // Free pixel data
    mov     x0, x1                  // x0 = pixel data pointer
    bl      free                    // free(pixel data)

skip_free_pixels:
    // Free Image struct
    mov     x0, x0                  // x0 = Image struct pointer
    bl      free                    // free(image)

destroy_image_done:
    ret

    .global get_width
//
// int get_width(void *image)
// Get the width of the image
//
get_width:
    // Parameters:
    // x0: image pointer

    ldr     w0, [x0, #image_width]  // w0 = image->width
    ret

    .global get_height
//
// int get_height(void *image)
// Get the height of the image
//
get_height:
    // Parameters:
    // x0: image pointer

    ldr     w0, [x0, #image_height] // w0 = image->height
    ret

    .global set_pixel
//
// void set_pixel(void *image, int row, int col, double value)
//
set_pixel:
    // Parameters:
    // x0: image pointer
    // w1: row
    // w2: col
    // d0: value

    // Zero-extend row and col to 64-bit registers
    uxtw    x1, w1                  // x1 = row
    uxtw    x2, w2                  // x2 = col

    // Load width and zero-extend
    ldr     w3, [x0, #image_width]  // w3 = image->width
    uxtw    x3, w3                  // x3 = width

    // Calculate index = row * width + col
    mul     x4, x1, x3              // x4 = row * width
    add     x4, x4, x2              // x4 = x4 + col

    // Calculate byte offset: offset = index * 8
    lsl     x4, x4, #3              // x4 = x4 << 3 (multiply by 8)

    // Load pixel data pointer
    ldr     x5, [x0, #image_pixels] // x5 = image->pixels

    // Compute pixel address
    add     x5, x5, x4              // x5 = x5 + x4

    // Store the double value into the pixel
    str     d0, [x5]                // *pixel = value

    ret

    .global get_pixel
//
// double get_pixel(void *image, int row, int col)
//
get_pixel:
    // Parameters:
    // x0: image pointer
    // w1: row
    // w2: col

    // Zero-extend row and col to 64-bit registers
    uxtw    x1, w1                  // x1 = row
    uxtw    x2, w2                  // x2 = col

    // Load width and zero-extend
    ldr     w3, [x0, #image_width]  // w3 = image->width
    uxtw    x3, w3                  // x3 = width

    // Calculate index = row * width + col
    mul     x4, x1, x3              // x4 = row * width
    add     x4, x4, x2              // x4 = x4 + col

    // Calculate byte offset: offset = index * 8
    lsl     x4, x4, #3              // x4 = x4 << 3 (multiply by 8)

    // Load pixel data pointer
    ldr     x5, [x0, #image_pixels] // x5 = image->pixels

    // Compute pixel address
    add     x5, x5, x4              // x5 = x5 + x4

    // Load the double value from the pixel
    ldr     d0, [x5]                // d0 = *pixel

    ret
