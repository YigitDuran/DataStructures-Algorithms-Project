#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct node {
    int user_id;
    int movie_id;
    double rating;
    node* left;
    node* right;
};

class binaryTree {
public:
    binaryTree() : root(nullptr) {}

    void insert(int user_id, int movie_id, double rating) {
        node* new_node = new node{user_id, movie_id, rating, nullptr, nullptr};
        if (root == nullptr) {
            root = new_node;
            return;
        }
        node* current = root;
        while (true) {
            if (user_id < current->user_id) {
                if (current->left == nullptr) {
                    current->left = new_node;
                    return;
                }
                current = current->left;
            } else if (user_id > current->user_id) {
                if (current->right == nullptr) {
                    current->right = new_node;
                    return;
                }
                current = current->right;
            } else {  // user_id == current->user_id
                if (movie_id < current->movie_id) {
                    if (current->left == nullptr) {
                        current->left = new_node;
                        return;
                    }
                    current = current->left;
                } else {  // movie_id >= current->movie_id
                    if (current->right == nullptr) {
                        current->right = new_node;
                        return;
                    }
                    current = current->right;
                }
            }
        }
    }

    std::vector<int> findRatedMovies(int user_id) const {
        std::vector<int> rated_movies;
        FindRatedMoviesSearch(root, user_id, rated_movies);
        return rated_movies;
    }

    std::vector<int> usersThatRated(int movie_id) const {
        std::vector<int> users;
        FindUsersWhoRatedMovieSearch(root, movie_id, users);
        return users;
    }

    std::vector<std::pair<int, int>> usersWithHighestRatings() const {
        std::unordered_map<int, int> rating_count;
        FindUsersWithMostRatingsSearch(root, rating_count);
        std::vector<std::pair<int, int>> rating_count_vec;
        for (const auto &kv: rating_count) {
            rating_count_vec.push_back(kv);
        }
        std::sort(rating_count_vec.begin(), rating_count_vec.end(),
                  [](const auto &p1, const auto &p2) { return p1.second > p2.second; });
        std::vector<std::pair<int, int>> top_users;
        for (int i = 0; i < 10 && i < rating_count_vec.size(); ++i) {
            top_users.push_back(rating_count_vec[i]);
        }
        return top_users;
    }

    std::vector<std::pair<int, int>> moviesWithHighestRatings() const {
        std::unordered_map<int, int> rating_count;
        FindMoviesWithMostRatingsSearch(root, rating_count);
        std::vector<std::pair<int, int>> rating_count_vec;
        for (const auto& kv : rating_count) {
            rating_count_vec.push_back(kv);
        }
        std::sort(rating_count_vec.begin(), rating_count_vec.end(),
                  [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
        std::vector<std::pair<int, int>> top_movies;
        for (int i = 0; i < 10 && i < rating_count_vec.size(); ++i) {
            top_movies.push_back(rating_count_vec[i]);
        }
        return top_movies;
    }

    void FindRatedMoviesSearch(node* node, int user_id, std::vector<int>& rated_movies) const {
        if (node == nullptr) return;
        if (node->user_id == user_id) {
            rated_movies.push_back(node->movie_id);
        }
        FindRatedMoviesSearch(node->left, user_id, rated_movies);
        FindRatedMoviesSearch(node->right, user_id, rated_movies);
    }

    void FindUsersWhoRatedMovieSearch(node* node, int movie_id, std::vector<int>& users) const {
        if (node == nullptr) return;
        if (node->movie_id == movie_id) {
            users.push_back(node->user_id);
        }
        FindUsersWhoRatedMovieSearch(node->left, movie_id, users);
        FindUsersWhoRatedMovieSearch(node->right, movie_id, users);
    }

    void FindUsersWithMostRatingsSearch(node* node, std::unordered_map<int, int>& rating_count) const {
        if (node == nullptr) return;
        ++rating_count[node->user_id];
        FindUsersWithMostRatingsSearch(node->left, rating_count);
        FindUsersWithMostRatingsSearch(node->right, rating_count);
    }

    void FindMoviesWithMostRatingsSearch(node* node, std::unordered_map<int, int>& rating_count) const {
        if (node == nullptr) return;
        ++rating_count[node->movie_id];
        FindMoviesWithMostRatingsSearch(node->left, rating_count);
        FindMoviesWithMostRatingsSearch(node->right, rating_count);
    }

private:
    node* root;
};

int main() {
    binaryTree data;

    std::ifstream input_file("train.txt");
    std::string line;
    while (std::getline(input_file, line)) {
        int user_id, movie_id;
        double rating;
        std::sscanf(line.c_str(), "%d,%d,%lf", &user_id, &movie_id, &rating);
        data.insert(user_id, movie_id, rating);
    }

    std::vector<std::pair<int, int>> top_users = data.usersWithHighestRatings();
    std::cout << "Top 10 users with the most number of ratings:\n";
    for (const auto& user : top_users) {
        std::cout << "User ID: " << user.first << ", Number of ratings: " << user.second << '\n';
    }

    std::vector<std::pair<int, int>> top_movies = data.moviesWithHighestRatings();
    std::cout << "\nTop 10 movies with the most number of ratings:\n";
    for (const auto& movie : top_movies) {
        std::cout << "Movie ID: " << movie.first << ", Number of ratings: " << movie.second << '\n';
    }

    return 0;
}