# MovieRatingAnalyzer

**Description:**

This C++ program analyzes movie ratings data from a text file. It utilizes a binary tree data structure to store ratings based on user ID and movie ID, enabling efficient retrieval and analysis.

**Functionality:**

* **Data Loading:** Reads movie ratings data from a text file (`train.txt`) in the format "user_id,movie_id,rating".
* **Binary Tree Storage:**
    - Inserts rating records into a binary tree, using a composite key (user ID, movie ID) for sorting.
    - Allows efficient searching and retrieval of ratings based on user or movie IDs.
* **Data Analysis:** Provides the following functions to analyze the stored data:
    - `findRatedMovies(int user_id)`: Finds all movies rated by a specific user.
    - `usersThatRated(int movie_id)`: Finds all users who have rated a specific movie. (Not used in the current `main` function)
    - `usersWithHighestRatings()`: Identifies the top 10 users who have rated the most movies.
    - `moviesWithHighestRatings()`: Identifies the top 10 movies with the most ratings.

**How to Use:**

1. **Compile:** Compile the code (e.g., `g++ main.cpp -o MovieRatingAnalyzer`).
2. **Prepare Data:** Make sure you have a `train.txt` file in the same directory as the executable, formatted as described above.
3. **Run:** Execute the compiled program (`./MovieRatingAnalyzer`).

**Example Output:**

Top 10 users with the most number of ratings:
User ID: 414, Number of ratings: 158
User ID: 599, Number of ratings: 118
...(other users)

Top 10 movies with the most number of ratings:
Movie ID: 356, Number of ratings: 329
Movie ID: 318, Number of ratings: 317
...(other movies)

**Additional Information:**
- This project is designed to work specifically with the MovieLens dataset, which should be provided in the "train.txt" file.

**Key Concepts Demonstrated:**

*   **Binary Trees:** Efficient storage and retrieval of structured data.
*   **File Input:** Reading data from a text file.
*   **Data Analysis:** Use of maps and vectors for counting and sorting.