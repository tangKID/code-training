/*
48. ��תͼ��

����һ�� n �� n �Ķ�ά�����ʾһ��ͼ��

��ͼ��˳ʱ����ת 90 �ȡ�
˵����

������� ԭ�� ��תͼ������ζ������Ҫֱ���޸�����Ķ�ά�����벻Ҫ ʹ����һ����������תͼ��
ʾ�� 1:

    ���� matrix =
    [
        [1,2,3],
        [4,5,6],
        [7,8,9]
    ],

    ԭ����ת�������ʹ���Ϊ:
    [
        [7,4,1],
        [8,5,2],
        [9,6,3]
    ]

ʾ�� 2:

    ���� matrix =
    [
        [ 5, 1, 9,11],
        [ 2, 4, 8,10],
        [13, 3, 6, 7],
        [15,14,12,16]
    ],

    ԭ����ת�������ʹ���Ϊ:
    [
        [15,13, 2, 5],
        [14, 3, 4, 1],
        [12, 6, 8, 9],
        [16, 7,10,11]
    ]
*/
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    
    
    for (int i = 0; i < matrixSize / 2; i++)
    {
        int start = i; // ��ǰ������ʼ�±꣨���ݾ���ȣ�
        int end = matrixSize - i - 1; // ��ǰ�����յ��±꣨���ݾ���ȣ�
        for (int j = 0; j < end - start; j++) {
            int temp = matrix[start][start + j];
            matrix[start][start + j] = matrix[end - j][start];
            matrix[end - j][start] = matrix[end][end - j];
            matrix[end][end - j] = matrix[start + j][end];
            matrix[start + j][end] = temp;
        }
    }
}