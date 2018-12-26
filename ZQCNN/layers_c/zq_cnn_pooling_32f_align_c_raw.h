void zq_cnn_maxpooling_nopadding_suredivided_kernel2x2(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	int n, out_h, out_w, c;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					//val = zq_mm_set1_ps(-FLT_MAX);
					cur_row_ptr = in_pix_ptr;

					cur_pix_ptr = cur_row_ptr;
					//val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					val = zq_mm_load_ps(cur_pix_ptr);
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					zq_mm_store_ps(out_pix_ptr, val);
				}
			}
		}
	}
}

void zq_cnn_avgpooling_nopadding_suredivided_kernel2x2(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	register zq_mm_type scale = zq_mm_set1_ps(1.0f / (kernel_H*kernel_W));
	int n, out_h, out_w, c;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					//val = zq_mm_set1_ps(0);
					cur_row_ptr = in_pix_ptr;

					cur_pix_ptr = cur_row_ptr;
					//val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					val = zq_mm_load_ps(cur_pix_ptr);
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, scale));
				}
			}
		}
	}
}


void zq_cnn_maxpooling_nopadding_suredivided_kernel3x3(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	int n, out_h, out_w, c;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					//val = zq_mm_set1_ps(-FLT_MAX);
					cur_row_ptr = in_pix_ptr;

					cur_pix_ptr = cur_row_ptr;
					//val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					val = zq_mm_load_ps(cur_pix_ptr);
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					zq_mm_store_ps(out_pix_ptr, val);
				}
			}
		}
	}
}

void zq_cnn_avgpooling_nopadding_suredivided_kernel3x3(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	register zq_mm_type scale = zq_mm_set1_ps(1.0f / (kernel_H*kernel_W));
	int n, out_h, out_w, c;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					//val = zq_mm_set1_ps(0);
					cur_row_ptr = in_pix_ptr;

					cur_pix_ptr = cur_row_ptr;
					//val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					val = zq_mm_load_ps(cur_pix_ptr);
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, scale));
				}
			}
		}
	}
}


void zq_cnn_maxpooling_nopadding_suredivided_kernel5x5(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	int n, out_h, out_w, c/*, kh, kw*/;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					//val = zq_mm_set1_ps(-FLT_MAX);
					cur_row_ptr = in_pix_ptr;

					cur_pix_ptr = cur_row_ptr;
					//val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					val = zq_mm_load_ps(cur_pix_ptr);
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));

					zq_mm_store_ps(out_pix_ptr, val);
				}
			}
		}
	}
}

void zq_cnn_avgpooling_nopadding_suredivided_kernel5x5(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	register zq_mm_type scale = zq_mm_set1_ps(1.0f / (kernel_H*kernel_W));
	int n, out_h, out_w, c/*, kh, kw*/;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					//val = zq_mm_set1_ps(0);
					cur_row_ptr = in_pix_ptr;

					cur_pix_ptr = cur_row_ptr;
					//val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					val = zq_mm_load_ps(cur_pix_ptr);
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					cur_row_ptr += in_widthStep;

					cur_pix_ptr = cur_row_ptr;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					cur_pix_ptr += in_pixelStep;
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));

					zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, scale));
				}
			}
		}
	}
}



void zq_cnn_maxpooling_nopadding_suredivided_general(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	int n, out_h, out_w, c, kh, kw;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					val = zq_mm_set1_ps(-FLT_MAX);
					for (kh = 0, cur_row_ptr = in_pix_ptr; kh < kernel_H; kh++, cur_row_ptr += in_widthStep)
					{
						for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < kernel_W; kw++, cur_pix_ptr += in_pixelStep)
						{
							val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
						}
					}
					zq_mm_store_ps(out_pix_ptr, val);
				}
			}
		}
	}
}

void zq_cnn_avgpooling_nopadding_suredivided_general(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	register zq_mm_type scale = zq_mm_set1_ps(1.0f / (kernel_H*kernel_W));
	int n, out_h, out_w, c, kh, kw;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;
	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					val = zq_mm_set1_ps(0);
					for (kh = 0, cur_row_ptr = in_pix_ptr; kh < kernel_H; kh++, cur_row_ptr += in_widthStep)
					{
						for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < kernel_W; kw++, cur_pix_ptr += in_pixelStep)
						{
							val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
						}
					}
					zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, scale));
				}
			}
		}
	}
}


void zq_cnn_maxpooling_nopadding_nodivided_general(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	int n, out_h, out_w, c, kh, kw;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;

	int final_kH = __min(kernel_H, in_H - (out_H - 1)*stride_H);
	int final_kW = __min(kernel_W, in_W - (out_W - 1)*stride_W);

	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H - 1;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W - 1;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					val = zq_mm_set1_ps(-FLT_MAX);
					for (kh = 0, cur_row_ptr = in_pix_ptr; kh < kernel_H; kh++, cur_row_ptr += in_widthStep)
					{
						for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < kernel_W; kw++, cur_pix_ptr += in_pixelStep)
						{
							val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
						}
					}
					zq_mm_store_ps(out_pix_ptr, val);
				}


				val = zq_mm_set1_ps(-FLT_MAX);
				for (kh = 0, cur_row_ptr = in_pix_ptr; kh < kernel_H; kh++, cur_row_ptr += in_widthStep)
				{
					for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < final_kW; kw++, cur_pix_ptr += in_pixelStep)
					{
						val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					}
				}
				zq_mm_store_ps(out_pix_ptr, val);
			}

			for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
				out_w < out_W - 1;
				out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
			{
				val = zq_mm_set1_ps(-FLT_MAX);
				for (kh = 0, cur_row_ptr = in_pix_ptr; kh < final_kH; kh++, cur_row_ptr += in_widthStep)
				{
					for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < kernel_W; kw++, cur_pix_ptr += in_pixelStep)
					{
						val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
					}
				}
				zq_mm_store_ps(out_pix_ptr, val);
			}


			val = zq_mm_set1_ps(-FLT_MAX);
			for (kh = 0, cur_row_ptr = in_pix_ptr; kh < final_kH; kh++, cur_row_ptr += in_widthStep)
			{
				for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < final_kW; kw++, cur_pix_ptr += in_pixelStep)
				{
					val = zq_mm_max_ps(val, zq_mm_load_ps(cur_pix_ptr));
				}
			}
			zq_mm_store_ps(out_pix_ptr, val);
		}
	}
}

void zq_cnn_avgpooling_nopadding_nodivided_general(
	const float* in_tensor4D_data,
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	int kernel_H,
	int kernel_W,
	int stride_H,
	int stride_W,
	float* out_tensor4D_data,
	int out_N,	// must be in_N
	int out_H,	// must be ceil((in_H - filter_H)/stride_H) + 1
	int out_W,	// must be ceil((in_W - filter_W)/stride_W) + 1
	int out_C,	// must be filter_N
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	register zq_mm_type val;
	register zq_mm_type scale = zq_mm_set1_ps(1.0f / (kernel_H*kernel_W));
	int n, out_h, out_w, c, kh, kw;
	const float* in_c_ptr, *in_pix_ptr, *in_row_ptr, *in_slice_ptr;
	float* out_c_ptr, *out_pix_ptr, *out_row_ptr, *out_slice_ptr;
	const float* cur_pix_ptr, *cur_row_ptr;
	int in_widthStep_mul_strideH = in_widthStep*stride_H;
	int in_pixelStep_mul_strideW = in_pixelStep*stride_W;

	int final_kH = __min(kernel_H, in_H - (out_H - 1)*stride_H);
	int final_kW = __min(kernel_W, in_W - (out_W - 1)*stride_W);

	for (n = 0, in_slice_ptr = in_tensor4D_data, out_slice_ptr = out_tensor4D_data;
		n < out_N;
		n++, in_slice_ptr += in_sliceStep, out_slice_ptr += out_sliceStep)
	{
		for (c = 0, in_c_ptr = in_slice_ptr, out_c_ptr = out_slice_ptr;
			c < out_C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			for (out_h = 0, out_row_ptr = out_c_ptr, in_row_ptr = in_c_ptr;
				out_h < out_H - 1;
				out_h++, out_row_ptr += out_widthStep, in_row_ptr += in_widthStep_mul_strideH)
			{
				for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
					out_w < out_W - 1;
					out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
				{
					val = zq_mm_set1_ps(0);
					for (kh = 0, cur_row_ptr = in_pix_ptr; kh < kernel_H; kh++, cur_row_ptr += in_widthStep)
					{
						for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < kernel_W; kw++, cur_pix_ptr += in_pixelStep)
						{
							val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
						}
					}
					zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, scale));
				}


				val = zq_mm_set1_ps(0);
				for (kh = 0, cur_row_ptr = in_pix_ptr; kh < kernel_H; kh++, cur_row_ptr += in_widthStep)
				{
					for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < final_kW; kw++, cur_pix_ptr += in_pixelStep)
					{
						val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					}
				}
				zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, zq_mm_set1_ps(1.0f / (kernel_H*final_kW))));
			}

			for (out_w = 0, out_pix_ptr = out_row_ptr, in_pix_ptr = in_row_ptr;
				out_w < out_W - 1;
				out_w++, out_pix_ptr += out_pixelStep, in_pix_ptr += in_pixelStep_mul_strideW)
			{
				val = zq_mm_set1_ps(0);
				for (kh = 0, cur_row_ptr = in_pix_ptr; kh < final_kH; kh++, cur_row_ptr += in_widthStep)
				{
					for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < kernel_W; kw++, cur_pix_ptr += in_pixelStep)
					{
						val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
					}
				}
				zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, zq_mm_set1_ps(1.0f / (final_kH*kernel_W))));
			}


			val = zq_mm_set1_ps(0);
			for (kh = 0, cur_row_ptr = in_pix_ptr; kh < final_kH; kh++, cur_row_ptr += in_widthStep)
			{
				for (kw = 0, cur_pix_ptr = cur_row_ptr; kw < final_kW; kw++, cur_pix_ptr += in_pixelStep)
				{
					val = zq_mm_add_ps(val, zq_mm_load_ps(cur_pix_ptr));
				}
			}
			zq_mm_store_ps(out_pix_ptr, zq_mm_mul_ps(val, zq_mm_set1_ps(1.0f / (final_kH*final_kW))));
		}
	}
}
