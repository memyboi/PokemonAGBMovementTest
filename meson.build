project('PokemonAGBMovement', 'c', 
  default_options : [
    'warning_level=2'
    ]
)

sdl2 = dependency('sdl2')
sdl2_image = dependency('sdl2_image')

add_project_arguments(
  [
    '-Wno-unused-parameter',
  ],
  language: 'c')

executable('PokemonAGBMovement', 'src/main.c', 'src/window.c', 'src/input.c', 'src/object.c', dependencies: [sdl2, sdl2_image])