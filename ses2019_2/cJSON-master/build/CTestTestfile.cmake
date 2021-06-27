# CMake generated Testfile for 
# Source directory: /home/owner/Desktop/programming/ses2019_2/cJSON-master
# Build directory: /home/owner/Desktop/programming/ses2019_2/cJSON-master/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/home/owner/Desktop/programming/ses2019_2/cJSON-master/build/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/home/owner/Desktop/programming/ses2019_2/cJSON-master/CMakeLists.txt;240;add_test;/home/owner/Desktop/programming/ses2019_2/cJSON-master/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
