#include <stdio.h>
#include <omp.h>
#include "../ZQ_CNN_CompileConfig.h"
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_SSE
#include <mmintrin.h> //MMX  
#include <xmmintrin.h> //SSE(include mmintrin.h)  
#include <emmintrin.h> //SSE2(include xmmintrin.h)  
#include <pmmintrin.h> //SSE3(include emmintrin.h)  
#include <tmmintrin.h>//SSSE3(include pmmintrin.h)  
#include <smmintrin.h>//SSE4.1(include tmmintrin.h)  
#include <nmmintrin.h>//SSE4.2(include smmintrin.h)  
#endif
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX
#include <wmmintrin.h>//AES(include nmmintrin.h)  
#include <immintrin.h>//AVX(include wmmintrin.h)  
#include <intrin.h>//(include immintrin.h)  
#endif

#if defined(__cplusplus) || defined(c_plusplus) 
extern "C" {
#endif

#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_SSE
#define zq_cnn_depthwise_conv_no_padding_32f_general zq_cnn_depthwise_conv_no_padding_32f_align128bit_general
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_1 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C4
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_2 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C8
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_4 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C16
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_8 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C32
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_16 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C64
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_32 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C128
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_64 zq_cnn_depthwise_conv_no_padding_32f_align128bit_kernel3x3_C256
#define zq_mm_load_ps _mm_load_ps
#define zq_mm_store_ps _mm_store_ps
#define zq_mm_add_ps _mm_add_ps
#if ZQ_CNN_USE_FMADD128
#define zq_mm_fmadd_ps _mm_fmadd_ps
#else
#define zq_mm_fmadd_ps(A, B, C) _mm_add_ps(_mm_mul_ps(A, B), C)
#endif
#define zq_mm_mul_ps _mm_mul_ps
#define zq_mm_setzero_ps _mm_setzero_ps
#define zq_mm_type __m128
#define zq_mm_align_size 4
#define zq_mm_align_size_mul_2 8
#define zq_mm_align_size_mul_3 12
#define zq_mm_align_size_mul_4 16
#define zq_mm_align_size_mul_5 20
#define zq_mm_align_size_mul_6 24
#define zq_mm_align_size_mul_7 28
#define zq_mm_align_size_mul_8 32
#define zq_mm_align_size_mul_16 64
#define zq_mm_align_size_mul_32 128
#define zq_mm_align_size_mul_64 256
#define zq_final_sum_q (q[0]+q[1]+q[2]+q[3])

#include "zq_cnn_depthwise_convolution_32f_align_c_raw.h"

#undef zq_cnn_depthwise_conv_no_padding_32f_general
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_1
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_2
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_4
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_8
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_16
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_32
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_64
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_add_ps
#undef zq_mm_fmadd_ps
#undef zq_mm_mul_ps
#undef zq_mm_setzero_ps
#undef zq_mm_type
#undef zq_mm_align_size
#undef zq_mm_align_size_mul_2
#undef zq_mm_align_size_mul_3
#undef zq_mm_align_size_mul_4
#undef zq_mm_align_size_mul_5
#undef zq_mm_align_size_mul_6
#undef zq_mm_align_size_mul_7
#undef zq_mm_align_size_mul_8
#undef zq_mm_align_size_mul_16
#undef zq_mm_align_size_mul_32
#undef zq_mm_align_size_mul_64
#undef zq_final_sum_q

#endif
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX

#define zq_cnn_depthwise_conv_no_padding_32f_general zq_cnn_depthwise_conv_no_padding_32f_align256bit_general
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_1 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C8
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_2 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C16
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_3 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C24
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_4 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C32
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_8 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C64
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_16 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C128
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_32 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C256
#define zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_64 zq_cnn_depthwise_conv_no_padding_32f_align256bit_kernel3x3_C512
#define zq_mm_load_ps _mm256_load_ps
#define zq_mm_store_ps _mm256_store_ps
#define zq_mm_add_ps _mm256_add_ps
#if ZQ_CNN_USE_FMADD256
#define zq_mm_fmadd_ps _mm256_fmadd_ps
#else
#define zq_mm_fmadd_ps(A, B, C) _mm256_add_ps(_mm256_mul_ps(A, B), C)
#endif
#define zq_mm_mul_ps _mm256_mul_ps
#define zq_mm_setzero_ps _mm256_setzero_ps
#define zq_mm_type __m256
#define zq_mm_align_size 8
#define zq_mm_align_size_mul_2 16
#define zq_mm_align_size_mul_3 24
#define zq_mm_align_size_mul_4 32
#define zq_mm_align_size_mul_5 40
#define zq_mm_align_size_mul_6 48
#define zq_mm_align_size_mul_7 56
#define zq_mm_align_size_mul_8 64
#define zq_mm_align_size_mul_16 128
#define zq_mm_align_size_mul_32 256
#define zq_mm_align_size_mul_64 512
#define zq_final_sum_q (q[0]+q[1]+q[2]+q[3]+q[4]+q[5]+q[6]+q[7])


#include "zq_cnn_depthwise_convolution_32f_align_c_raw.h"


#undef zq_cnn_depthwise_conv_no_padding_32f_general
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_1
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_2
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_3
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_4
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_8
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_16
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_32
#undef zq_cnn_depthwise_conv_no_padding_32f_kernel3x3_mul_64
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_add_ps
#undef zq_mm_fmadd_ps
#undef zq_mm_mul_ps
#undef zq_mm_setzero_ps
#undef zq_mm_type
#undef zq_mm_align_size
#undef zq_mm_align_size_mul_2
#undef zq_mm_align_size_mul_3
#undef zq_mm_align_size_mul_4
#undef zq_mm_align_size_mul_5
#undef zq_mm_align_size_mul_6
#undef zq_mm_align_size_mul_7
#undef zq_mm_align_size_mul_8
#undef zq_mm_align_size_mul_16
#undef zq_mm_align_size_mul_32
#undef zq_mm_align_size_mul_64
#undef zq_final_sum_q
#endif


	void zq_cnn_depthwise_conv_no_padding_32f_align0_general(
		const float* in_tensor4D_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep,
		const float* filters_data,
		int filter_N, // must be 1
		int filter_H, // 
		int filter_W, // 
		int filter_C, // must be in_C
		int filter_pixelStep,
		int filter_widthStep,
		int filter_sliceStep,
		int stride_H,
		int stride_W,
		float* out_tensor4D_data,
		int out_N,	// must be in_N
		int out_H,	// must be (in_H - filter_H)/stride_H + 1
		int out_W,	// must be (in_W - filter_W)/stride_W + 1
		int out_C,	// must be in_C
		int out_pixelStep,
		int out_widthStep,
		int out_sliceStep
	)
	{

		const float* in_slice_ptr;
		const float* in_row_ptr;
		const float* in_pix_ptr;
		float* out_slice_ptr;
		float* out_row_ptr;
		float* out_pix_ptr;
		float* out_c_ptr;

		const float* cur_in_row_ptr;
		const float* cur_in_pix_ptr;
		const float* cur_in_c_ptr;
		const float* cur_filter_row_ptr;
		const float* cur_filter_pix_ptr;
		const float* cur_filter_c_ptr;

		int stride_H_mul_in_WidthStep = stride_H*in_widthStep;
		int stride_W_mul_in_pixStep = stride_W*in_pixelStep;
		int out_n, out_h, out_w, out_c, kh, kw, kc;

		for (out_n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
			out_n < out_N;
			out_n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
		{
			for (out_h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
				out_h < out_H;
				out_h++, in_row_ptr += stride_H_mul_in_WidthStep, out_row_ptr += out_widthStep)
			{
				for (out_w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
					out_w < out_W;
					out_w++, in_pix_ptr += stride_W_mul_in_pixStep, out_pix_ptr += out_pixelStep)
				{
					for (out_c = 0, out_c_ptr = out_pix_ptr; out_c < in_C; out_c++, out_c_ptr++)
						*out_c_ptr = 0;


					for (kh = 0, cur_in_row_ptr = in_pix_ptr, cur_filter_row_ptr = filters_data;
						kh < filter_H;
						kh++, cur_in_row_ptr += in_widthStep, cur_filter_row_ptr += filter_widthStep)
					{
						for (kw = 0, cur_in_pix_ptr = cur_in_row_ptr, cur_filter_pix_ptr = cur_filter_row_ptr;
							kw < filter_W;
							kw++, cur_in_pix_ptr += in_pixelStep, cur_filter_pix_ptr += filter_pixelStep)
						{
							for (kc = 0, cur_in_c_ptr = cur_in_pix_ptr, cur_filter_c_ptr = cur_filter_pix_ptr, out_c_ptr = out_pix_ptr;
								kc < in_C;
								kc++, cur_in_c_ptr++, cur_filter_c_ptr++, out_c_ptr++)
							{
								*out_c_ptr += (*cur_in_c_ptr)*(*cur_filter_c_ptr);
							}
						}
					}

				}
			}
		}
	}



#if defined(__cplusplus) || defined(c_plusplus) 
}
#endif