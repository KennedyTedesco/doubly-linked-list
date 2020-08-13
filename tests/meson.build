unity_dep = dependency('unity',
    fallback : ['unity', 'unity_dep']
)

test('list',
    executable('test_list',
        ['test_list.c', '../list.c', '../iterator.c'],
        dependencies: unity_dep
    )
)
