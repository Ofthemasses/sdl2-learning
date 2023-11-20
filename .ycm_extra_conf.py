def Settings(**kwargs):
    return {
        'flags': ['-x', 'c++', '-Wall', '-I./glad/include', '-L/path/to/libs', '-lSDL2', '-ldl'],
    }

