add_test (NAME qcor_quasimo_python_bindings
  COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_quasimo.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(qcor_quasimo_python_bindings
    PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")

add_test (NAME qcor_python_jit_simple
 COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_jit_simple.py 
 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(qcor_python_jit_simple
   PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")

add_test (NAME qcor_python_jit_nested_kernels
 COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_jit_nested.py 
 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(qcor_python_jit_nested_kernels
   PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")

add_test (NAME qcor_python_jit_decompose
 COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_jit_decompose.py 
 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(qcor_python_jit_decompose
   PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")

add_test (NAME qcor_test_qcor_spec_api
   COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_qcor_spec_api.py 
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
 )
 set_tests_properties(qcor_test_qcor_spec_api
     PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")

add_test (NAME qcor_kernel_ftqc_python
 COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_kernel_ftqc.py -qrt ftqc
 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(qcor_kernel_ftqc_python
   PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")

add_test (NAME qcor_python_jit_pass_manager
   COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_jit_pass_manager.py
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
 )
 set_tests_properties(qcor_python_jit_pass_manager
     PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}:$ENV{PYTHONPATH}")