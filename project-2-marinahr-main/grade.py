
from gggg import *

a = Assignment(36, 18)
s = State(a)

horizontal_rule()

s.reject_if_missing_contributors()
s.reject_if_starter_contributors()

s.reject_unless_files_exist(['poly_exp.hpp',
                             'poly_exp_test.cpp'])

s.reject_if_file_unchanged('poly_exp.cpp',
                           '8269fd340255c02f1c33eb86d8df4dfe0ddf822acdff2aa569e412edd87cf5a3')

s.reject_if_file_changed('poly_exp_test.cpp',
                         '126e0d8ff80a4abcd57f6655f6e28c410bdbfe983226f2ca44115a161565a9af')

s.reject_unless_command_succeeds(['make', 'clean', 'build'])

s.string_removed_test('TODO comments removed', 6, 'TODO', ['poly_exp.cpp'])

s.gtest_run('poly_exp_test')
s.gtest_suite_test('max_subarray_exh_SmallCases', 6)
s.gtest_suite_test('max_subarray_exh_LargeCases', 6)
s.gtest_suite_test('max_subarray_dbh_SmallCases', 6)
s.gtest_suite_test('max_subarray_dbh_LargeCases', 6)
s.gtest_suite_test('subset_sum_exh', 6)

s.summarize()