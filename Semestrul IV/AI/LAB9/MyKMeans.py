import math

import numpy as np
from scipy.spatial.distance import cdist


class MyKMeans:
    def __init__(self, n_clusters, max_iter=300):
        self.n_clusters = n_clusters
        self.max_iter = max_iter

    def fit(self, X):
        X = X.toarray()
        # se aleg random indexi din lista
        idx = np.random.choice(X.shape[0], self.n_clusters, replace=False)
        self.centroids = X[idx]

        # se updateaza centroidul
        for _ in range(self.max_iter):
            labels = self._assign_clusters(X)
            new_centroids = self._update_centroids(X, labels)
            if np.allclose(self.centroids, new_centroids):
                break

            self.centroids = new_centroids

    # fiecare punct = cluster
    def _assign_clusters(self, X):
        #calculez distanta euclidiana per centroid
        distances = []
        for centroid in self.centroids:
            centroid_distances = []
            for x in X:
                distance = math.sqrt(sum([(a - b) ** 2 for a, b in zip(x, centroid)]))
                centroid_distances.append(distance)
            distances.append(centroid_distances)
        return [np.argmin(dists) for dists in zip(*distances)]

    def _update_centroids(self, X, labels):
        new_centroids = np.zeros_like(self.centroids)
        for i in range(self.n_clusters):
            cluster_points = X[labels == i]
            if len(cluster_points) > 0:
                new_centroids[i] = np.mean(cluster_points, axis=1)
        return new_centroids

    def predict(self, X):
        distances = cdist(X, self.centroids, 'euclidean')
        #caut indicele minim per coloana
        labels = np.argmin(distances, axis=1)
        return labels
