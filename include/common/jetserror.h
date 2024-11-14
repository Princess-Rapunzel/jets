#ifndef __ERROR_H__
#define __ERROR_H__

// C includes.s
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>

#define DEBUG
// #define HAVE_MPI
#define HAVE_OPENMP

#ifdef DEBUG

pthread_mutex_t _error_mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t _error_cond_ = PTHREAD_COND_INITIALIZER;
int error_flag = 0;
char error_message[256];


#define JETS_ERROR_REPORT(msg) \
    do { \
        char time_str[20]; \
        pthread_mutex_lock(&_error_mutex_); \
        time_t rawtime; \
        struct tm *timeinfo; \
        time(&rawtime); \
        timeinfo = localtime(&rawtime); \
        strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M:%S", timeinfo); \
        snprintf(error_message, sizeof(error_message), "[%s]Error in File \"%s\", line %d:\n\t%s", time_str, __FILE__, __LINE__, msg); \
        error_flag = 1; \
        pthread_cond_signal(&_error_cond_); \
        pthread_mutex_unlock(&_error_mutex_); \
    } while (0)

#define JETS_NOT_IMPLEMENTED_MSG(msg) \
    do { \
        char time_str[20]; \
        pthread_mutex_lock(&_error_mutex_); \
        time_t rawtime; \
        struct tm *timeinfo; \
        time(&rawtime); \
        timeinfo = localtime(&rawtime); \
        strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M:%S", timeinfo); \
        snprintf(error_message, sizeof(error_message), "[%s]Error in File \"%s\", line %d:\n\tFunction \"%s\" not implemented yet. %s", time_str, __FILE__, __LINE__, __func__, msg); \
        error_flag = 1; \
        pthread_cond_signal(&_error_cond_); \
        pthread_mutex_unlock(&_error_mutex_); \
    } while (0)

#define JETS_NOT_IMPLEMENTED JETS_NOT_IMPLEMENTED_MSG("")

#define JETS_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            JETS_ERROR_REPORT("Assertion failed."); \
        } \
    } while (0)

#define JETS_ASSERT_EQUAL(expr1, expr2) \
    do { \
        if (!((expr1) == (expr2))) { \
            JETS_ERROR_REPORT("Assertion `" #expr1 " == " #expr2 "' failed.\n"); \
        } \
    } while (0)
#else
#define JETS_ERROR_REPORT(msg) ((void) 0)
#define JETS_NOT_IMPLEMENTED ((void) 0)
#define JETS_ASSERT(cond) ((void) 0)
#define JETS_ASSERT_EQUAL(expr1, expr2) ((void) 0)
#define JETS_NOT_IMPLEMENTED_MSG(msg) ((void) 0)
#define JETS_NOT_IMPLEMENTED ((void) 0)
#endif // DEBUG

#define VECTOR_DIMN_EQUAL(vec1, vec2) JETS_ASSERT_EQUAL(vec1->n, vec2->n)
#define VECTOR_DIMN_LOCAL_EQUAL(vec1, vec2) JETS_ASSERT_EQUAL(vec1->local_n, vec2->local_n)
#define MATRIX_COMPATIBLE(mat1, mat2) JETS_ASSERT_EQUAL(mat1->col, mat2->raw)
#define MATRIX_SQUARE(mat) JETS_ASSERT_EQUAL(mat->raw, mat->col)
#define MATRIX_VECTOR_COMPATIBLE(mat, vec) JETS_ASSERT_EQUAL(mat->col, vec->n)

#ifndef __cplusplus
#define throw
#define MatrixDimNotEqualError JETS_ERROR_REPORT("Matrix dimensions are not equal.")
#endif // __cplusplus
#endif //__ERROR_H__