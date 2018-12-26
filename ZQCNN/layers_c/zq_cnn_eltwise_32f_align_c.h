#ifndef _ZQ_CNN_ELTWISE_32F_ALIGN_C_H_
#define _ZQ_CNN_ELTWISE_32F_ALIGN_C_H_
#include "../ZQ_CNN_CompileConfig.h"
#if defined(__cplusplus) || defined(c_plusplus) 
extern "C" {
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
	);


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
	);

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
	);


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
	);

#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_SSE
	void zq_cnn_eltwise_sum_32f_align128bit(
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
	);

	void zq_cnn_eltwise_sum_with_weight_32f_align128bit(
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
	);

	void zq_cnn_eltwise_mul_32f_align128bit(
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
	);

	void zq_cnn_eltwise_max_32f_align128bit(
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
	);

#endif

#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX
	void zq_cnn_eltwise_sum_32f_align256bit(
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
	);

	void zq_cnn_eltwise_sum_with_weight_32f_align256bit(
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
	);

	void zq_cnn_eltwise_mul_32f_align256bit(
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
	);

	void zq_cnn_eltwise_max_32f_align256bit(
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
	);
#endif

#if defined(__cplusplus) || defined(c_plusplus) 
}
#endif

#endif