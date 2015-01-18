base_env = Environment(CPPFLAGS="-stdlib=libc++ -Wall -Wextra -Werror -std=c++11 -pedantic -fsanitize=undefined",
                       CPPPATH='#src',
                       CXX='clang++')

debug_env = base_env.Clone()
debug_env.MergeFlags("-O0 -g")

release_env = base_env.Clone()
release_env.MergeFlags("-O2 -DNDEBUG")

debug_exports = {
    'env': debug_env,
    'prefix': ''
}

release_exports = {
    'env': release_env,
    'prefix': 'release_'
}

SConscript("src/SConscript", exports=debug_exports, variant_dir='.debug_build')
SConscript("src/SConscript", exports=release_exports, variant_dir='.release_build')

Alias('test', '#bin/test')

Default('test')
