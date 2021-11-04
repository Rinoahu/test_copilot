// smith-waterman algorithm accelerated by intel avx2 instructions
int smith_waterman_avx2(char *seq1, char *seq2, int len1, int len2, int *score, int *pos1, int *pos2)
{ 
  int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
  int max_score, max_i, max_j, max_k, max_l, max_m, max_n, max_o, max_p, max_q, max_r, max_s, max_t, max_u, max_v, max_w, max_x, max_y, max_z;
  int max_score_avx2, max_i_avx2, max_j_avx2, max_k_avx2, max_l_avx2, max_m_avx2, max_n_avx2, max_o_avx2, max_p_avx2, max_q_avx2, max_r_avx2, max_s_avx2, max_t_avx2, max_u_avx2, max_v_avx2, max_w_avx2, max_x_avx2, max_y_avx2, max_z_avx2;
  int score_avx2[len1+1][len2+1];
  int pos1_avx2[len1+1][len2+1];
  int pos2_avx2[len1+1][len2+1];
  int score_avx2_tmp[len1+1][len2+1];
  int pos1_avx2_tmp[len1+1][len2+1];
  int pos2_avx2_tmp[len1+1][len2+1];
  int score_avx2_tmp2[len1+1][len2+1];
  int pos1_avx2_tmp2[len1+1][len2+1];
  int pos2_avx2_tmp2[len1+1][len2+1];
