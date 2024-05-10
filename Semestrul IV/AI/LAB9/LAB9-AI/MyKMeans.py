import numpy as np


class myKMeans:

    def __init__(self, n_clusters=8, max_iter=300):
        self.n_clusters = n_clusters
        self.max_iter = max_iter

    def fit(self, X):

        # Pasul 1: Inițializăm centroizii aleatori
        self.centroids = X[np.random.choice(X.shape[0], self.n_clusters, replace=False)]

        for _ in range(self.max_iter):
            # Pasul 2: Atribuim fiecare punct celui mai apropiat centroid
            labels = self._assign_labels(X)

            # Pasul 3: Recalculăm centroizii
            new_centroids = self._calculate_centroids(X, labels)

            # Verificăm dacă algoritmul converge
            if np.allclose(new_centroids, self.centroids):
                break

            self.centroids = new_centroids

    def predict(self, X):
        labels = self._assign_labels(X)
        return labels

    def _assign_labels(self, X):
        print("Dimensiunea lui X:", X.shape)
        print("Dimensiunea centroidilor:", self.centroids.shape)
        labels = np.argmin(np.linalg.norm(X[:, np.newaxis] - self.centroids, axis=2), axis=1)
        return labels

    def _calculate_centroids(self, X, labels):
        centroids = np.array([X[labels == i].mean(axis=0) for i in range(self.n_clusters)])
        return centroids