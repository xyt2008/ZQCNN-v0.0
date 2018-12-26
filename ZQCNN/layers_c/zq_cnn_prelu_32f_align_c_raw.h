#define op_0_4 \
	a0 = zq_mm_load_ps(c_ptr);\
	b0 = zq_mm_load_ps(slope_c_ptr);\
	a1 = zq_mm_load_ps(c_ptr+zq_mm_align_size);\
	b1 = zq_mm_load_ps(slope_c_ptr+zq_mm_align_size);\
	a2 = zq_mm_load_ps(c_ptr+zq_mm_align_size_mul_2);\
	b2 = zq_mm_load_ps(slope_c_ptr+zq_mm_align_size_mul_2);\
	a3 = zq_mm_load_ps(c_ptr+zq_mm_align_size_mul_3);\
	b3 = zq_mm_load_ps(slope_c_ptr+zq_mm_align_size_mul_3);\
	c0 = zq_mm_min_ps(zero_v,a0);\
	c1 = zq_mm_min_ps(zero_v,a1);\
	c2 = zq_mm_min_ps(zero_v,a2);\
	c3 = zq_mm_min_ps(zero_v,a3);\
	d0 = zq_mm_max_ps(zero_v,a0);\
	d1 = zq_mm_max_ps(zero_v,a1);\
	d2 = zq_mm_max_ps(zero_v,a2);\
	d3 = zq_mm_max_ps(zero_v,a3);\
	zq_mm_store_ps(c_ptr, zq_mm_fmadd_ps(b0,c0,d0));\
	zq_mm_store_ps(c_ptr+zq_mm_align_size, zq_mm_fmadd_ps(b1,c1,d1));\
	zq_mm_store_ps(c_ptr+zq_mm_align_size_mul_2, zq_mm_fmadd_ps(b2,c2,d2));\
	zq_mm_store_ps(c_ptr+zq_mm_align_size_mul_3, zq_mm_fmadd_ps(b3,c3,d3));\
	c_ptr += zq_mm_align_size_mul_4;\
	slope_c_ptr += zq_mm_align_size_mul_4

#define op_0_4_lessthan1 \
	a0 = zq_mm_load_ps(c_ptr);\
	b0 = zq_mm_load_ps(slope_c_ptr);\
	a1 = zq_mm_load_ps(c_ptr+zq_mm_align_size);\
	b1 = zq_mm_load_ps(slope_c_ptr+zq_mm_align_size);\
	a2 = zq_mm_load_ps(c_ptr+zq_mm_align_size_mul_2);\
	b2 = zq_mm_load_ps(slope_c_ptr+zq_mm_align_size_mul_2);\
	a3 = zq_mm_load_ps(c_ptr+zq_mm_align_size_mul_3);\
	b3 = zq_mm_load_ps(slope_c_ptr+zq_mm_align_size_mul_3);\
	c0 = zq_mm_mul_ps(a0, b0);\
	c1 = zq_mm_mul_ps(a1, b1);\
	c2 = zq_mm_mul_ps(a2, b2);\
	c3 = zq_mm_mul_ps(a3, b3);\
	d0 = zq_mm_max_ps(a0, c0);\
	d1 = zq_mm_max_ps(a1, c1);\
	d2 = zq_mm_max_ps(a2, c2);\
	d3 = zq_mm_max_ps(a3, c3);\
	zq_mm_store_ps(c_ptr, d0);\
	zq_mm_store_ps(c_ptr+zq_mm_align_size, d1);\
	zq_mm_store_ps(c_ptr+zq_mm_align_size_mul_2, d2);\
	zq_mm_store_ps(c_ptr+zq_mm_align_size_mul_3, d3);\
	c_ptr += zq_mm_align_size_mul_4;\
	slope_c_ptr += zq_mm_align_size_mul_4

#define op_0_8 \
	op_0_4;\
	op_0_4

#define op_0_8_lessthan1 \
	op_0_4_lessthan1;\
	op_0_4_lessthan1

#define op_0_16 \
	op_0_8;\
	op_0_8

#define op_0_16_lessthan1 \
	op_0_8_lessthan1;\
	op_0_8_lessthan1

#define op_0_32 \
	op_0_16;\
	op_0_16

#define op_0_32_lessthan1 \
	op_0_16_lessthan1;\
	op_0_16_lessthan1

#define op_0_64 \
	op_0_32;\
	op_0_32

#define op_0_64_lessthan1 \
	op_0_32_lessthan1;\
	op_0_32_lessthan1

/*
y = max(0,x)+a*min(0,x)
*/
void zq_cnn_prelu_32f_align(
	float* in_tensor4D_data,	// in & out
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	const float* slope_data
)
{
	register zq_mm_type value_v;
	register zq_mm_type slope_v;
	int n, h, w, c;
	const float *slope_c_ptr;
	float* slice_ptr, *row_ptr, *pix_ptr, *c_ptr;
	register zq_mm_type  a0, a1, a2, a3;
	register zq_mm_type  b0, b1, b2, b3;
	register zq_mm_type  c0, c1, c2, c3;
	register zq_mm_type  d0, d1, d2, d3;
	register zq_mm_type zero_v = zq_mm_setzero_ps();

	if (in_C % zq_mm_align_size_mul_32 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr, slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_32)
					{	
						op_0_32;
					}
				}
			}
		}
	}
	else if (in_C % zq_mm_align_size_mul_16 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr, slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_16)
					{
						op_0_16;
					}
				}
			}
		}
	}
	else if (in_C % zq_mm_align_size_mul_8 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr, slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_8)
					{
						op_0_8;
					}
				}
			}
		}
	}
	else if (in_C % zq_mm_align_size_mul_4 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr, slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_8)
					{
						op_0_4;
					}
				}
			}
		}
	}
	else
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr, slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size)
					{
						value_v = zq_mm_load_ps(c_ptr);
						slope_v = zq_mm_load_ps(slope_c_ptr);
						zq_mm_store_ps(c_ptr, zq_mm_fmadd_ps(slope_v, zq_mm_min_ps(zq_mm_setzero_ps(), value_v), zq_mm_max_ps(zq_mm_setzero_ps(), value_v)));
						c_ptr += zq_mm_align_size; slope_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
	}
}

void zq_cnn_prelu_32f_align_sure_slope_lessthan1(
	float* in_tensor4D_data,	// in & out
	int in_N,
	int in_H,
	int in_W,
	int in_C,
	int in_pixelStep,
	int in_widthStep,
	int in_sliceStep,
	const float* slope_data
)
{
	register zq_mm_type data_v;
	int n, h, w, c;
	float* slice_ptr, *row_ptr, *pix_ptr, *c_ptr;
	const float* slope_c_ptr;
	register zq_mm_type  a0, a1, a2, a3;
	register zq_mm_type  b0, b1, b2, b3;
	register zq_mm_type  c0, c1, c2, c3;
	register zq_mm_type  d0, d1, d2, d3;

#if 1
	if (in_C % zq_mm_align_size_mul_32 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr,slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_32)
					{
						op_0_32_lessthan1;
					}
				}
			}
		}

	}
	else if (in_C % zq_mm_align_size_mul_16 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr,slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_16)
					{
						op_0_16_lessthan1;
					}
				}
			}
		}
	}
	else if (in_C % zq_mm_align_size_mul_8 == 0)
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr,slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size_mul_8)
					{
						op_0_8_lessthan1;
					}
				}
			}
		}
	}
	else
	{
		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr,slope_c_ptr = slope_data; c < in_C; c += zq_mm_align_size)
					{
						data_v = zq_mm_load_ps(c_ptr);
						zq_mm_store_ps(c_ptr, zq_mm_max_ps(data_v, zq_mm_mul_ps(data_v, zq_mm_load_ps(slope_c_ptr))));
						c_ptr += zq_mm_align_size; slope_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
	}
	
#else

	for (c = 0, c_ptr = in_tensor4D_data; c < in_C; c += zq_mm_align_size, c_ptr += zq_mm_align_size)
	{
		slope_v = zq_mm_load_ps(slope_data + c);

		for (n = 0, slice_ptr = c_ptr; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					data_v = zq_mm_load_ps(pix_ptr);
					data_v = zq_mm_max_ps(data_v, zq_mm_mul_ps(data_v, slope_v));
					zq_mm_store_ps(pix_ptr, data_v);
				}
			}
		}
	}
#endif
}


#undef op_0_4
#undef op_0_8
#undef op_0_16
#undef op_0_32
#undef op_0_64
#undef op_0_4_lessthan1
#undef op_0_8_lessthan1
#undef op_0_16_lessthan1
#undef op_0_32_lessthan1
#undef op_0_64_lessthan1
