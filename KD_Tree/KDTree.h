#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

class KDTree {
private:
    struct KDNode {
        std::vector<float> point;
        KDNode *left, *right;

        KDNode(const std::vector<float> &pt);
    };

    KDNode* root;
    KDNode* insertRec(KDNode* node, const std::vector<float> &point, unsigned depth);
    bool searchRec(KDNode* node, const std::vector<float> &point, unsigned depth);
    KDNode* deleteRec(KDNode* node, const std::vector<float> &point, unsigned depth);
    KDNode* findMinRec(KDNode* node, unsigned dim, unsigned depth);
    bool arePointsEqual(const std::vector<float> &point1, const std::vector<float> &point2);
    void clear(KDNode* node);

public:
    KDTree();
    ~KDTree();
    void insert(const std::vector<float> &point);
    bool search(const std::vector<float> &point);
    void deletePoint(const std::vector<float> &point);
};

#endif // KDTREE_H
