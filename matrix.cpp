#include <iostream>

class Matrix{
    public: 
        double **matrix;
        int r_size, c_size;
        Matrix(int n){
            r_size = c_size = n;
            matrix = new double*[n];
            for(int i = 0; i < n; i++){
                double *vector = new double[n];
                matrix[i] = vector;
            }
        }

        void del(){
            for(int i = 0; i < r_size; i++)
                delete[] matrix[i];
            delete[] matrix;
        }

        std::string inspect(){
            std::string s;
            s = "[\n";
            for(int r = 0; r < r_size; r++){
                s += "    [";
                for(int c = 0; c < c_size; c++){
                    s += std::to_string(matrix[r][c]) + (c_size == c + 1 ? "" : ", ");
                }
                s += (std::string)"]" + (r_size == r + 1 ? "" : ",") + "\n";
            }
            s += "]";
            return s;
        }

        Matrix p(){
            std::cout << inspect() << std::endl;
            return *this;
        }

        Matrix copy(){
            Matrix mat(r_size);
            for(int i = 0; i < r_size; i++)
                for(int j = 0; j < c_size; j++)
                    mat.matrix[i][j] = matrix[i][j];
            return mat;
        }

        static Matrix identity(int n){
            Matrix mat(n);
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++){
                    mat.matrix[i][j] = i == j ? 1 : 0;
                }
            return mat;
        }

        Matrix inv(){
            int n = r_size;
            Matrix matrix = copy();
            Matrix e = identity(n);
            for(int i = 0; i < n - 1; i++){
                double ii = matrix.matrix[i][i];
                for(int j = i + 1; j < n; j++){
                    double ji = matrix.matrix[j][i];
                    for(int k = 0; k < n; k++){
                        matrix.matrix[j][k] -= ji / ii * matrix.matrix[i][k];
                        e.matrix[j][k] -= ji / ii * e.matrix[i][k];
                    }
                }
            }

            for(int i = n - 1; i >= 1; i--){
                double p = matrix.matrix[i][i];
                for(int k = 0; k < n; k++){
                    matrix.matrix[i][k] /= p;
                    e.matrix[i][k] /= p;
                }

                for(int j = i - 1; j >= 0; j--){
                    double p = -matrix.matrix[j][i];
                    for(int k = 0; k < n; k++){
                        matrix.matrix[j][k] += p * matrix.matrix[i][k];
                        e.matrix[j][k] += p * e.matrix[i][k];
                    }
                }
            }
            matrix.del();
            return e;
        }

};