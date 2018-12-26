#include <stdlib.h>
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
#define zq_cnn_eltwise_sum_32f_align zq_cnn_eltwise_sum_32f_align128bit
#define zq_cnn_eltwise_sum_with_weight_32f_align zq_cnn_eltwise_sum_with_weight_32f_align128bit
#define zq_cnn_eltwise_mul_32f_align zq_cnn_eltwise_mul_32f_align128bit
#define zq_cnn_eltwise_max_32f_align zq_cnn_eltwise_max_32f_align128bit
#define zq_mm_load_ps _mm_load_ps
#define zq_mm_store_ps _mm_store_ps
#define zq_mm_mul_ps _mm_mul_ps
#define zq_mm_add_ps _mm_add_ps
#define zq_mm_max_ps _mm_max_ps
#define zq_mm_set1_ps _mm_set1_ps
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

#include "zq_cnn_eltwise_32f_align_c_raw.h"


#undef zq_cnn_eltwise_sum_32f_align
#undef zq_cnn_eltwise_sum_with_weight_32f_align
#undef zq_cnn_eltwise_mul_32f_align
#undef zq_cnn_eltwise_max_32f_align
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_mul_ps
#undef zq_mm_add_ps
#undef zq_mm_max_ps
#undef zq_mm_set1_ps
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
#endif

#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX
#define zq_cnn_eltwise_sum_32f_align zq_cnn_eltwise_sum_32f_align256bit
#define zq_cnn_eltwise_sum_with_weight_32f_align zq_cnn_eltwise_sum_with_weight_32f_align256bit
#define zq_cnn_eltwise_mul_32f_align zq_cnn_eltwise_mul_32f_align256bit
#define zq_cnn_eltwise_max_32f_align zq_cnn_eltwise_max_32f_align256bit
#define zq_mm_load_ps _mm256_load_ps
#define zq_mm_store_ps _mm256_store_ps
#define zq_mm_mul_ps _mm256_mul_ps
#define zq_mm_add_ps _mm256_add_ps
#define zq_mm_max_ps _mm256_max_ps
#define zq_mm_set1_ps _mm256_set1_ps
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

#include "zq_cnn_eltwise_32f_align_c_raw.h"


#undef zq_cnn_eltwise_sum_32f_align
#undef zq_cnn_eltwise_sum_with_weight_32f_align
#undef zq_cnn_eltwise_mul_32f_align
#undef zq_cnn_eltwise_max_32f_align
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_mul_ps
#undef zq_mm_add_ps
#undef zq_mm_max_ps
#undef zq_mm_set1_ps
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
#endif

	void zq_cnn_eltwise_sum_32f_align0(
		int in_tensor_num,	//must be >=2
		const float** in_tensor4D_data,
		int N,
		int H,
		int W,
		int C,
		const int* in_pixelStep,
		const int* in_widthStep,
		const int* in_sliceStep,
		float* out_tensor4D_data,
		int out_pixeStep,
		int out_widthStep,
		int out_sliceStep
	)
	{
		int n, h, w, c, tensor_id;
		const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
		const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
		float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixeStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c++, in_c_ptr++, in1_c_ptr++, out_c_ptr++)
					{
						*out_c_ptr = (*in_c_ptr) + (*in1_c_ptr);
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixeStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;
							c++, in_c_ptr++, out_c_ptr++)
						{
							*out_c_ptr += (*in_c_ptr);
						}
					}
				}
			}
		}
	}


	void zq_cnn_eltwise_sum_with_weight_32f_align0(
		int in_tensor_num,	//must be >=2
		const float** in_tensor4D_data,
		const float* weight,
		int N,
		int H,
		int W,
		int C,
		const int* in_pixelStep,
		const int* in_widthStep,
		const int* in_sliceStep,
		float* out_tensor4D_data,
		int out_pixeStep,
		int out_widthStep,
		int out_sliceStep
	)
	{
		int n, h, w, c, tensor_id;
		const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
		const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
		float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixeStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c++, in_c_ptr++, in1_c_ptr++, out_c_ptr++)
					{
						*out_c_ptr = (*in_c_ptr)*weight[0] + (*in1_c_ptr)*weight[1];
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixeStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;
							c++, in_c_ptr++, out_c_ptr++)
						{
							*out_c_ptr += (*in_c_ptr)*weight[tensor_id];
						}
					}
				}
			}
		}
	}


	void zq_cnn_eltwise_mul_32f_align0(
		int in_tensor_num,	//must be >=2
		const float** in_tensor4D_data,
		int N,
		int H,
		int W,
		int C,
		const int* in_pixelStep,
		const int* in_widthStep,
		const int* in_sliceStep,
		float* out_tensor4D_data,
		int out_pixeStep,
		int out_widthStep,
		int out_sliceStep
	)
	{
		int n, h, w, c, tensor_id;
		const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
		const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
		float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixeStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c++, in_c_ptr++, in1_c_ptr++, out_c_ptr++)
					{
						*out_c_ptr = (*in_c_ptr) * (*in1_c_ptr);
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixeStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;
							c++, in_c_ptr++, out_c_ptr++)
						{
							*out_c_ptr *= (*in_c_ptr);
						}
					}
				}
			}
		}
	}


	void zq_cnn_eltwise_max_32f_align0(
		int in_tensor_num,	//must be >=2
		const float** in_tensor4D_data,
		int N,
		int H,
		int W,
		int C,
		const int* in_pixelStep,
		const int* in_widthStep,
		const int* in_sliceStep,
		float* out_tensor4D_data,
		int out_pixeStep,
		int out_widthStep,
		int out_sliceStep
	)
	{
		int n, h, w, c, tensor_id;
		const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
		const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
		float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixeStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c++, in_c_ptr++, in1_c_ptr++, out_c_ptr++)
					{
						*out_c_ptr = __max((*in_c_ptr), (*in1_c_ptr));
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixeStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;
							c++, in_c_ptr++, out_c_ptr++)
						{
							*out_c_ptr = __max((*out_c_ptr), (*in_c_ptr));
						}
					}
				}
			}
		}
	}


#if defined(__cplusplus) || defined(c_plusplus) 
}
#endif