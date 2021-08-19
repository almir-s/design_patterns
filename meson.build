project('Design patterns', 'cpp', default_options:['cpp_std=c++14'])

source_dir = files([])

boost_dep = dependency('boost')

project_dep = declare_dependency(sources: source_dir, dependencies: [boost_dep])


subdir('command')
subdir('flyweight')
subdir('observer')
subdir('singleton')
executable('main', sources: ['src/main.cpp'], dependencies: [project_dep])
