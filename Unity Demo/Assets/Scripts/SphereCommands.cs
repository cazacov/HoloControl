using UnityEngine;

public class SphereCommands : MonoBehaviour
{
    // Use this for initialization
    void Start()
    {
    }

    private float scale = 3.0f;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.A))
        {
            transform.RotateAround(transform.position, Vector3.up, 2);
        }

        if (Input.GetKey(KeyCode.D))
        {
            transform.RotateAround(transform.position, Vector3.up, -2);
        }

        if (Input.GetKey(KeyCode.W))
        {
            transform.RotateAround(transform.position, Vector3.right, 2);
        }

        if (Input.GetKey(KeyCode.S))
        {
            transform.RotateAround(transform.position, Vector3.right, -2);
        }

        if (Input.GetKey(KeyCode.Escape))
        {
            scale *= 0.99f;
            transform.localScale = new Vector3(scale, scale,scale);
        }

        if (Input.GetKey(KeyCode.Return))
        {
            scale *= 1.01f;
            transform.localScale = new Vector3(scale, scale, scale);
        }
    }
}