
ADD_EXECUTABLE(test_mysql test_mysql.cpp)
TARGET_LINK_LIBRARIES(test_mysql media_access mysql_dao)

ADD_EXECUTABLE(simple_test simple_test.cpp)
TARGET_LINK_LIBRARIES(simple_test image_provider media_access mysql_dao ${OpenCV_LIBS} t_util)
